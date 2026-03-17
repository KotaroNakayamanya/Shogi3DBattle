#include"DX12.h"

#include<algorithm>
#include<cassert>

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    // デバッグ有効化
    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer = nullptr;

        D3D12GetDebugInterface(
            IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

        debugLayer->EnableDebugLayer();
    }
}


// DirectX12初期処理
bool DX12::InitDX12(GameWindow* gameWindow)
{
    // ファクトリー系作成
    if (FAILED(CreateDXGIFactory())) goto failed; // DXGIファクトリー作成
    if (FAILED(_dxgiFactory->CreateAdapter(_adapter.get()))) goto failed; // アダプター作成
    if (FAILED(_dxgiFactory->CreateDevice(_device.get(), _adapter.get()))) goto failed; // デバイス作成
    _adapter.reset(); // アダプター破棄

    // コマンド作成
    if (FAILED(_device->CreateCmdAllocator(_cmdAllocator.get()))) goto failed; // コマンドアロケータ作成
    if (FAILED(_device->CreateCmdList(_cmdList.get(), _cmdAllocator.get()))) goto failed; // コマンドリスト作成
    if (FAILED(_device->CreateCmdQueue(_cmdQueue.get()))) goto failed; // コマンドキュー作成

    // スワップチェーン作成
    if (FAILED(_dxgiFactory->CreateSwapChain(_swapChain.get(), _cmdQueue.get(), gameWindow))) goto failed;
    // RTVヒープ作成
    if (FAILED(_device->CreateRTVHeap(_rtvHeap.get(), _swapChain.get()))) goto failed;
    // RTV作成
    UINT rtBuffNum; // レンダーターゲット数
    rtBuffNum = _swapChain->GetRTBuffNum();
    _rtvs.resize(rtBuffNum);
    for (int i = 0; i < rtBuffNum; i++)
    {
        _rtvs[i] = std::make_unique<RTV>();
        if (FAILED(_device->CreateRTV(_rtvs[i].get(), _rtvHeap.get(), _swapChain.get(), i))) goto failed;
    }

    //// デプスステンシルバッファ作成
    if (FAILED(_device->CreateDSBuff(_dsBuff.get(), gameWindow))) goto failed;
    //// DSVヒープ作成
    if (FAILED(_device->CreateDSVHeap(_dsvHeap.get()))) goto failed;
    _device->CreateDSV(_dsv.get(), _dsvHeap.get(), _dsBuff.get()); // DSV作成

    
    if (FAILED(_device->CreateFence(_fence.get()))) goto failed; // フェンス作成

    _viewport->SetViewport(gameWindow); // ビューポート作成
    _scissorRect->SetScissorRect(gameWindow); // シザー矩形作成

    // シェーダー作成
    if (FAILED(_device->CreateVShader(_vShader.get()))) goto failed; // 頂点シェーダーバイナリオブジェクト作成
    if (FAILED(_device->CreatePShader(_pShader.get()))) goto failed; // ピクセルシェーダーバイナリオブジェクト作成

    // 頂点・インデックスバッファ作成
    CreateBoard();
    CreatePiece();
    if (FAILED(_device->CreateVertBuff(_vertBuff.get(), _board.get(), _pawn.get()))) goto failed; // 頂点バッファ作成
    if (FAILED(_device->CreateIdxBuff (_idxBuff.get(),  _board.get(), _pawn.get()))) goto failed; // インデックスバッファ作成
    if (FAILED(_vertBuff->WriteToVertBuff(_board.get(), _pawn.get()))) goto failed; // 頂点バッファに書き込み
    if (FAILED(_idxBuff ->WriteToIdxBuff (_board.get(), _pawn.get())))  goto failed; // インデックスバッファに書き込み
    _device->CreateInputLayout(_inputLayout.get()); // 入力レイアウト（頂点バッファの中身の内訳）作成

    // 将棋オブジェクトにGPUアドレスを付与
    D3D12_GPU_VIRTUAL_ADDRESS vertBuffAddress, idxBuffAddress;

    vertBuffAddress  = _vertBuff->GetAddress();
    idxBuffAddress   = _idxBuff ->GetAddress();
    _board->SetVertAddress(vertBuffAddress);
    _board->SetIdxAddress (idxBuffAddress);

    vertBuffAddress += _board->GetVerticesByteSize(); // 将棋盤のバイトサイズを足してずらす
    idxBuffAddress  += _board->GetIndicesByteSize();  
    _pawn->SetVertAddress(vertBuffAddress);
    _pawn->SetIdxAddress (idxBuffAddress);


    // コンスタントバッファ、テクスチャバッファ作成
    if (FAILED(_device->CreateConstBuff(_constBuff.get(), 1))) goto failed; // コンスタントバッファ作成
    if (FAILED(_device->CreateTexBuff(_texBuff.get()))) goto failed; // テクスチャバッファ作成

    // CBV, SRV作成
    if (FAILED(_device->CreateCSUHeap(_csuHeap.get()))) goto failed; // CSUヒープオブジェクト作成
    _device->CreateCBV(_csuHeap.get(), _constBuff.get()); // CBV作成
    _device->CreateSRV(_csuHeap.get(), _texBuff.get());   // SRV作成
    //_device->CreateSRV(_srv.get(), _csuHeap.get(), _texBuff.get());   // SRV作成

    
    if (FAILED(_device->CreateRootSignature(_rootSignature.get()))) goto failed; // ルートシグネチャオブジェクト作成
    

    // パイプラインオブジェクト作成
    if (FAILED(_device->CreatePipeline(
        _pipeline.get(),      // パイプライン
        _rootSignature.get(), // ルートシグネチャ
        _inputLayout.get(),   // 入力レイアウト
        _vShader.get(),       // 頂点シェーダ
        _pShader.get())))     // ピクセルシェーダ
        goto failed;

    return true;

failed:
    assert(false);
    return false;
}

// DXGIファクトリー作成
HRESULT DX12::CreateDXGIFactory()
{
    HRESULT result;

    // デバッグモードのときは詳細を表示させるファクトリーを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory->_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory->_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}

void DX12::CreateBoard()
{
    std::vector<VertexStruct::Vertex> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{ 0.0f,  0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 0}, // 左下
        {{50.0f,  0.0f, 0.0f},  {0.0f, 0.0f, -11.0f}, {0.0f, 0.0f}, 0}, // 右下
        {{ 0.0f, 50.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 0}, // 左上
        {{50.0f, 50.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 0}, // 右上

        // 背面
        {{ 0.0f,  0.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 0}, // 左下
        {{50.0f,  0.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 0}, // 右下
        {{ 0.0f, 50.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 0}, // 左上
        {{50.0f, 50.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 0}  // 右上
    };

    _board->SetVertices(vertices);


    std::vector<unsigned short> indices;

    enum BoardVertName // 将棋盤の頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
    };

    indices =
    {
        // 前面
        frontRightBottom, frontLeftBottom,  frontLeftTop,
        frontLeftTop,     frontRightTop,    frontRightBottom,     
        
        // 上側面
        frontRightTop, frontLeftTop, backLeftTop, 
        backLeftTop,   backRightTop, frontRightTop,

        // 右側面
        frontRightBottom, frontRightTop,   backRightTop,
        backRightTop,     backRightBottom, frontRightBottom,

        // 下側面
        frontLeftBottom, frontRightBottom, backRightBottom,
        backRightBottom, backLeftBottom,   frontLeftBottom,

        // 左側面
        frontLeftTop, frontLeftBottom, backLeftBottom,
        backLeftBottom, backLeftTop, frontLeftTop,

        // 背面
        backRightBottom, backLeftBottom, backLeftTop,
        backLeftTop,     backRightTop,   backRightBottom
    };
    _board->SetIndices(indices);
}
void DX12::CreatePiece()
{
    std::vector<VertexStruct::Vertex> vertices;

    float bottomWidth  = 0.9f;          // 底面の横の長さ
    float cornerWidth  = 0.7f;          // 角部分の横の長さ
    float height       = 0.9f;          // 高さ
    float cornerHeight = height * 0.7f; // 角部分の高さ（高さを基準に調整）
    float thickness    = 0.4f;          // 駒の厚み

    vertices = // 頂点集合
    {   // 上面図と考えて指定
        // 前面
        {{-bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 1}, // 左下
        {{ bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 1}, // 右下
        {{-cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 1}, // 左上
        {{ cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 1}, // 右上
        {{ 0.0f,         height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, 1}, // 上    

        // 裏面
        {{-bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 1}, // 左下
        {{ bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 1}, // 右下
        {{-cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 1}, // 左上
        {{ cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 1}, // 右上
        {{ 0.0f,         height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 1}, // 上
    };

    _pawn->SetVertices(vertices);


    std::vector<unsigned short> indices;

    enum PieceVertName // 駒の頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上
        frontTop,         // 上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
        backTop          // 上
    };

    indices = // インデックス集合
    {
        // 前面
        frontRightBottom, frontLeftBottom, frontLeftTop,     // 右下　左下　左上
        frontLeftTop,     frontRightTop,   frontRightBottom, // 左上　右上 右下
        frontTop,         frontRightTop,   frontLeftTop,     // 右上　左上　上

        // 裏面
        backLeftBottom,  backRightBottom, backLeftTop, // 左下　右下　左上
        backRightBottom, backRightTop,    backLeftTop, // 右下　右上　左上
        backLeftTop,     backRightTop,    backTop,     // 左上　右上　上

        // 側面上左
        frontTop, frontLeftTop, backLeftTop, // 前面上　前面左上　背面左上
        backTop,  frontTop,     backLeftTop, // 背面上　前面上　　背面左上

        // 側面上右
        backTop,  backRightTop, frontRightTop, // 背面上　背面右上　前面右上
        frontTop, backTop,      frontRightTop, // 前面上　背面上　　前面右上　


        // 側面右
        frontRightBottom, frontRightTop, backRightBottom, // 背面右下　前面右上　背面右下
        frontRightTop,    backRightTop,  backRightBottom, // 背面右上　背面右上　背面右下

        // 側面左
        backLeftBottom, backLeftTop,  frontLeftBottom, // 背面左下　背面左上　前面左下
        backLeftTop,    frontLeftTop, frontLeftBottom, // 背面左上　前面左上　前面左下

        // 底面
        frontLeftBottom, frontRightBottom, backRightBottom, // 前面左下　前面右下　背面右下
        frontLeftBottom, backRightBottom, backLeftBottom    // 前面左下　背面右下　背面左下
    };

    _pawn->SetIndices(indices);
 }




// コマンド実行
void DX12::ExeDX12()
{
    // レンダーターゲットの準備をする
    PrepareRenderTarget();

    // ワールド行列を変換

    // コマンドセット
    SetCommand();

    // 描画実行
    ExeDraw();
    return;
}

// レンダーターゲット準備
void DX12::PrepareRenderTarget()
{
    // バックバッファインデックス取得
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();

    // ハンドル取得
    auto rtvHandle = _rtvs[backBufferIdx]->GetRTVHandle();
    auto dsvHandle = _dsv->GetDSVHandle();
    //rtvHandle.ptr += backBufferIdx * _rtvOffset;

    // RTVをレンダーターゲットに変更
    ChangeRTVBarrierToRenderTarget(_rtvs[backBufferIdx].get());

     // バックバッファをレンダーターゲットに設定
    _cmdList->SetRenderTarget(rtvHandle, dsvHandle);

    // レンダーターゲットクリア
    _cmdList->ClearRenderTarget(rtvHandle);
     // デプスステンシルクリア
    _cmdList->ClearDepthStencil(dsvHandle); 
}

// RTVリソースをレンダーターゲットに変更
void DX12::ChangeRTVBarrierToRenderTarget(RTV* rtv)
{
    D3D12_RESOURCE_BARRIER resourceBarrier = 
        GetBasiceResourceBarrier();

    resourceBarrier.Transition.pResource =
        rtv->GetRTV();
    resourceBarrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    resourceBarrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _cmdList->SetResourceBarrier(resourceBarrier);
}

// リソースバリア基本設定
D3D12_RESOURCE_BARRIER DX12::GetBasiceResourceBarrier()
{
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type =
        D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags =
        D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    return barrier;
}





// コマンドセット（Drawクラス）
void DX12::SetCommand()
{
    // パイプラインセット
    _cmdList->SetPipeline(_pipeline->GetPipelineState());

    // ルートシグネチャセット
    _cmdList->SetRootSignature(_rootSignature->GetRootSignature());

    // CBV,SRVヒープセット
    ID3D12DescriptorHeap* csuHeaps[] = {_csuHeap->GetCSUHeap()};
    auto csuHeapNum = sizeof(csuHeaps) / sizeof(ID3D12DescriptorHeap*);
    _cmdList->SetCSUHeaps(csuHeapNum, csuHeaps); 

    // ルートパラメータとディスクリプタ関連付け
    //_cmdList->SetDescriptorTable(0, _cbv->GetCBVHandle()); // CBV
    auto handle = _csuHeap->GetCSUHeap()->GetGPUDescriptorHandleForHeapStart();
    _cmdList->SetDescriptorTable(0, handle); // CBV
    handle.ptr += _device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    _cmdList->SetDescriptorTable(1, handle); // SRV

    // トポロジーセット
    _cmdList->SetTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // ビューポートセット
    D3D12_VIEWPORT viewports[] = {_viewport->GetViewport()};
    auto viewportNum = sizeof(viewports) / sizeof(D3D12_VIEWPORT);
    _cmdList->SetViewports(viewportNum, viewports);

    // シザー矩形セット
    D3D12_RECT scissorRects[] = {_scissorRect->GetScissorRect()};
    auto scissorRectNum = sizeof(scissorRects) / sizeof(D3D12_RECT);
    _cmdList->SetScissorRects(scissorRectNum, scissorRects);

        // ワールド行列、ビュープロジェクション行列をコンスタントバッファに書き込み
    _constBuff->WriteToConstBuff(
        _board.get(),
        _pawn.get(),
        _viewMat.get(),
        _projMat.get());


    // 将棋オブジェクト描画命令セット
    SetCmdDrawObj(_pawn.get());
    SetCmdDrawObj(_board.get());

        //_constBuff->WriteToConstBuff(
        //_board.get(),
        //_viewMat.get(),
        //_projMat.get());
    

    //// 頂点バッファビューセット
    //D3D12_VERTEX_BUFFER_VIEW vertBuffViews[] = {GetVertBuffView(_pawn.get())};
    //auto vertBuffViewNum = sizeof(vertBuffViews) / sizeof(D3D12_VERTEX_BUFFER_VIEW);
    //_cmdList->SetVertBuffViews(vertBuffViewNum, vertBuffViews);
    //// インデックスバッファセット
    //_cmdList->SetIdxBuffView(GetIdxBuffView(_pawn.get()));
    //// インデックス描画セット
    //_cmdList->SetDrawWithIdx(_pawn.get());
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertBuffView(ShogiObj* shogiObj)
{
    D3D12_VERTEX_BUFFER_VIEW view;

    view.BufferLocation =
        shogiObj->GetVertAddress();
    view.SizeInBytes =
        shogiObj->GetVerticesByteSize();
    view.StrideInBytes =
        shogiObj->GetVertexByteSize();

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIdxBuffView(ShogiObj* shogiObj)
{
    D3D12_INDEX_BUFFER_VIEW view;

    view.BufferLocation =
        shogiObj->GetIdxAddress();
    view.Format =
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =
        shogiObj->GetIndicesByteSize();

    return view;
}

// オブジェクト描画命令セット
void DX12::SetCmdDrawObj(ShogiObj* shogiObj)
{

    // 頂点バッファビューセット
    D3D12_VERTEX_BUFFER_VIEW vertBuffViews[] = {GetVertBuffView(shogiObj)};
    auto vertBuffViewNum = sizeof(vertBuffViews) / sizeof(D3D12_VERTEX_BUFFER_VIEW);
    _cmdList->SetVertBuffViews(vertBuffViewNum, vertBuffViews);

    // インデックスバッファセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(shogiObj));

    // インデックス描画セット
    _cmdList->SetDrawWithIdx(shogiObj);
}




// 描画実行
void DX12::ExeDraw()
{
     // バックバッファインデックス取得
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();
    
    
    ChangeRTVBarrierToPresent(_rtvs[backBufferIdx].get()); // RTVを表示画面に設定
    ExeCommand(); // コマンド実行
    _swapChain->Flip(); // 画面フリップ

}

// RTVリソースを画面表示に変更
void DX12::ChangeRTVBarrierToPresent(RTV* rtv)
{
    D3D12_RESOURCE_BARRIER barrier =
        GetBasiceResourceBarrier();

    barrier.Transition.pResource =
        rtv->GetRTV();
    barrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _cmdList->SetResourceBarrier(barrier);
}




// コマンド実行
void DX12::ExeCommand()
{
    _cmdList->GetCmdList()->Close(); // コマンドクローズ

    ID3D12CommandList* commandLists[] = {_cmdList->GetCmdList()}; // リストに格納
    UINT listNum = sizeof(commandLists) / sizeof(ID3D12CommandList); // リスト数取得

    _cmdQueue->GetCmdQueue()->ExecuteCommandLists(listNum, commandLists); // コマンドキュー実行

    WaitProcessWithFence(); // フェンスによる同期処理

    ResetCommand(); // コマンドリセット
}

// フェンスによる同期制御
void DX12::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _cmdQueue->GetCmdQueue()->Signal(_fence->GetFence(), _fence->GetIncrementFenceVal());

    while (_fence->GetFence()->GetCompletedValue() != _fence->GetFenceVal())
    {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        _fence->GetFence()->SetEventOnCompletion(_fence->GetFenceVal(), event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}

// コマンドリセット
void DX12::ResetCommand()
{
    ID3D12CommandAllocator* commandAllocator =
        _cmdAllocator->GetCmdAllocator();

    commandAllocator->Reset();
    _cmdList->GetCmdList()->Reset(commandAllocator, nullptr);
}




//// 描画設定更新
//HRESULT Draw::UpdateDrawConf(
//    ID3D12Device* device,
//    UINT width, 
//    UINT height,
//    UINT buffNum)
//{
//    WaitProcessWithFence(); // GPUが処理中であれば待つ
//    
//    _rtvHeap->ClearRTV(); // RTV破棄
//    if(FAILED(_swapChain->UpdateSwapChain( // スワップチェーン更新
//        width, height)))
//    {
//        assert(false); return E_FAIL;
//    }
//    if (FAILED(_rtvHeap->CreateRTV( // RTV再作成
//        device, _swapChain->GetSwapChain(), buffNum)))
//    {
//        assert(false); return E_FAIL;
//    }
//
//    return S_OK;
//}




//////
Piece* DX12::GetPawn(){return _pawn.get();} // 歩を返す}
ViewMat* DX12::GetViewMat(){return _viewMat.get();} // ビュー行列を返す
//////



//// ウインドウサイズ変更処理
//void DX12::ProcessChangeWindowSize(UINT width, UINT height)
//{   
//    // スワップチェーン更新
//    _draw->UpdateDrawConf(
//        _device->GetDevice(),
//        width, 
//        height,
//        _rtBuffNum);
//}

DX12::DX12() {
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _viewMat = std::make_unique<ViewMat>();
    _projMat = std::make_unique<ProjMat>();

    _dxgiFactory = std::make_unique<DXGIFactory>();
    _adapter     = std::make_unique<Adapter>();
    _device      = std::make_unique<Device>();

    _cmdAllocator = std::make_unique<CmdAllocator>();
    _cmdList      = std::make_unique<CmdList>();
    _cmdQueue     = std::make_unique<CmdQueue>();

    _swapChain = std::make_unique<SwapChain>();

    _rtvHeap      = std::make_unique<RTVHeap>();

    _dsBuff  = std::make_unique<DSBuff>();
    _dsvHeap = std::make_unique<DSVHeap>();
    _dsv     = std::make_unique<DSV>();

    _fence = std::make_unique<Fence>();

    _viewport    = std::make_unique<Viewport>();
    _scissorRect = std::make_unique<ScissorRect>();

    _vShader       = std::make_unique<VShader>();
    _pShader       = std::make_unique<PShader>();
    _vertBuff      = std::make_unique<VertBuff>();
    _idxBuff       = std::make_unique<IdxBuff>();
    _texBuff       = std::make_unique<TexBuff>();
    _constBuff     = std::make_unique<ConstBuff>();

    _csuHeap       = std::make_unique<CSUHeap>();
    //_srv           = std::make_unique<SRV>();
    _rootSignature = std::make_unique<RootSignature>();
    _inputLayout   = std::make_unique<InputLayout>();
    _pipeline      = std::make_unique<Pipeline>();

    _pawn = std::make_unique<Pawn>();
    _board = std::make_unique<Board>();
}

DX12::~DX12(){}