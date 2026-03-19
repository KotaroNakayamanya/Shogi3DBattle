#include"DX12.h"

#include<algorithm>
#include<cassert>
#include<Pawn.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwrite.lib")

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


    // レンダーターゲット系作成
    if (FAILED(_dxgiFactory->CreateSwapChain(_swapChain.get(), _cmdQueue.get(), gameWindow))) goto failed; // スワップチェーン作成
    if (FAILED(_device->CreateRTVHeap(_rtvHeap.get(), _swapChain.get()))) goto failed; // RTVヒープ作成
    UINT rtBuffNum; // レンダーターゲット数
    rtBuffNum = _swapChain->GetRTBuffNum();
    _backBuffs.resize(rtBuffNum);
    for (UINT i = 0; i < rtBuffNum; i++)
    {
        _backBuffs[i] = std::make_unique<BackBuff>();
        if (FAILED(_device->CreateBackBuff(_backBuffs[i].get(), _swapChain.get(), i))) goto failed; // バックバッファ作成
        _device->CreateRTV(_backBuffs[i].get(), _rtvHeap.get(), i); // RTV作成
    }


    // DirectX11系作成（文字描画に使用）
    if (FAILED(CreateDWriteFactory())) goto failed; // DirectWriteファクトリー作成
    if (FAILED(_device->CreateD3D11(_device11.get(), _deviceContext.get(), _cmdQueue.get()))) goto failed; // Direct3D11系作成
    if (FAILED(_device11->CreateD2DDeviceContext(_d2dDeviceContext.get()))) goto failed; // Direct2Dデバイスコンテキスト作成
    _wrappedBackBuffers.resize(rtBuffNum);
    _d2dRenderTargets.resize(rtBuffNum);
    for (UINT i = 0; i < rtBuffNum; i++)
    {
        _wrappedBackBuffers[i] = std::make_unique<WrappedBackBuffer>();
        _d2dRenderTargets[i]   = std::make_unique<D2DRenderTarget>();

        if (FAILED(_device11->CreateWrappedBackBuffer(_wrappedBackBuffers[i].get(), _backBuffs[i].get()))) goto failed; // ラップされたバックバッファ作成
        if (FAILED(_d2dDeviceContext->CreateD2DRenderTarget(_d2dRenderTargets[i].get(), _wrappedBackBuffers[i].get()))) goto failed; // Direct2Dレンダーターゲット作成
    }
    if(FAILED(_d2dDeviceContext->CreateD2DSolidColorBrush(_d2dSolidColorBrush.get()))) goto failed; // ソリッドカラーブラッシュ作成
    if(FAILED(_dWriteFactory->CreateDWriteTextFormat(_dWriteTextFormat.get(), L"メイリオ"))) goto failed; // テキストフォーマット作成
    if(FAILED(_dWriteFactory->CreateDWriteTextFormat(_pieceTextFormat.get(), L"メイリオ"))) goto failed; // 駒のテキストフォーマット作成


    // デプスステンシル系作成
    if (FAILED(_device->CreateDSBuff(_dsBuff.get(), gameWindow))) goto failed; // デプスステンシルバッファ作成
    if (FAILED(_device->CreateDSVHeap(_dsvHeap.get()))) goto failed; // DSVヒープ作成
    _device->CreateDSV(_dsvHeap.get(), _dsBuff.get()); // DSV作成


    // フェンス作成
    if (FAILED(_device->CreateFence(_fence.get()))) goto failed;


    // 描画領域系作成
    _viewport->SetViewport(gameWindow); // ビューポート作成
    _scissorRect->SetScissorRect(gameWindow); // シザー矩形作成


    // シェーダー作成
    if (FAILED(_device->CreateVShader(_vShader.get()))) goto failed; // 頂点シェーダー作成
    if (FAILED(_device->CreatePShader(_pShader.get()))) goto failed; // ピクセルシェーダー作成


    // 将棋オブジェクト作成
    CreateBoard(BOARD); // 将棋盤作成
    for (int i = 0; i < _pieces.size(); i++)
    {
        _pieces[i] = std::make_unique<Pawn>();
        if(i == 0)
            CreatePiece(_pieces[0].get(), PAWN_1);
        else
            CreatePiece(_pieces[i].get(), PAWN_2);
    }


    // 頂点・インデックスバッファ作成
    if (FAILED(_device->CreateVertBuff(_vertBuff.get(), _board.get(), _pieces))) goto failed; // 頂点バッファ作成
    if (FAILED(_device->CreateIdxBuff (_idxBuff.get(),  _board.get(), _pieces))) goto failed; // インデックスバッファ作成
    if (FAILED(_vertBuff->WriteToVertBuff(_board.get(), _pieces))) goto failed; // 頂点バッファに書き込み
    if (FAILED(_idxBuff ->WriteToIdxBuff (_board.get(), _pieces)))  goto failed; // インデックスバッファに書き込み
    _device->CreateInputLayout(_inputLayout.get()); // 入力レイアウト（頂点バッファの中身の内訳）作成


    // 将棋オブジェクトに頂点バッファアドレスを付与
    D3D12_GPU_VIRTUAL_ADDRESS vertBuffAddress, idxBuffAddress;

    vertBuffAddress  = _vertBuff->GetAddress();
    idxBuffAddress   = _idxBuff ->GetAddress();
    _board->SetVertAddress(vertBuffAddress);
    _board->SetIdxAddress (idxBuffAddress);

    vertBuffAddress += _board->GetVerticesByteSize(); // 将棋盤のバイトサイズを足してずらす
    idxBuffAddress  += _board->GetIndicesByteSize();  
    _pieces[0]->SetVertAddress(vertBuffAddress);
    _pieces[0]->SetIdxAddress(idxBuffAddress);

    vertBuffAddress += _pieces[0]->GetVerticesByteSize(); // 将棋盤のバイトサイズを足してずらす
    idxBuffAddress  += _pieces[0]->GetIndicesByteSize();
    _pieces[1]->SetVertAddress(vertBuffAddress);
    _pieces[1]->SetIdxAddress(idxBuffAddress);


    // コンスタントバッファ、テクスチャバッファ作成
    if (FAILED(_device->CreateConstBuff(_constBuff.get(), 40))) goto failed; // コンスタントバッファ作成
    if (FAILED(_device->CreateTexBuff(_texBuff.get()))) goto failed; // テクスチャバッファ作成

    CreateTex(); // テクスチャ作成
    _texBuff->WriteToTexBuff(_tex.get()); // テクスチャをバッファに書き込み
    


    // CBV, SRV作成
    UINT cbvNum, srvNum, uavNum;
    cbvNum = 1;
    srvNum = 1;
    uavNum = 0;
    if (FAILED(_device->CreateCSUHeap(_csuHeap.get(), cbvNum, srvNum, uavNum))) goto failed; // CSUヒープオブジェクト作成
    _device->CreateCBV(_csuHeap.get(), _constBuff.get()); // CBV作成
    _device->CreateSRV(_csuHeap.get(), _texBuff.get());   // SRV作成

    // 駒テクスチャ作成
    UINT shogiTexNum;
    shogiTexNum = 8 + 6 + 1; // 駒表8種 駒裏6種 将棋盤1
    _pieceTexBuffs.resize(shogiTexNum);
    for (UINT i = 0; i < shogiTexNum; i++)
    {
        _pieceTexBuffs[i] = std::make_unique<RenderTexBuff>();
        if (FAILED(_device->CreateRenderTexBuff(_pieceTexBuffs[i].get(), _backBuffs[0].get()))) goto failed; // レンダーターゲットテクスチャ作成
    }
    // if (FAILED(_device->CreateRTVHeap(_rtvHeap.get(), _swapChain.get()))) goto failed; // 駒テクスチャRTVヒープ作成
    
    

    // ルートシグネチャオブジェクト作成
    if (FAILED(_device->CreateRootSignature(_rootSignature.get()))) goto failed;


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

// DirectWriteファクトリー作成
HRESULT DX12::CreateDWriteFactory()
{
    return DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(_dWriteFactory->_dWriteFactory.ReleaseAndGetAddressOf()));
}

// 将棋盤作成
void DX12::CreateBoard(ShogiObjId id)
{
    _board->SetId(id);

    std::vector<ShogiObj::Vert> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{ 0.0f,  0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{50.0f,  0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, UINT(id)}, // 右下
        {{ 0.0f, 50.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, UINT(id)}, // 左上
        {{50.0f, 50.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, UINT(id)}, // 右上

        // 背面
        {{ 0.0f,  0.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{50.0f,  0.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 右下
        {{ 0.0f, 50.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左上
        {{50.0f, 50.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}  // 右上
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

// 駒作成
 void DX12::CreatePiece(Piece* piece, ShogiObjId id)
{
    piece->SetId(id);

    std::vector<ShogiObj::Vert> vertices;

    float bottomWidth  = 0.9f;          // 底面の横の長さ
    float cornerWidth  = 0.7f;          // 角部分の横の長さ
    float height       = 0.9f;          // 高さ
    float cornerHeight = height * 0.7f; // 角部分の高さ（高さを基準に調整）
    float thickness    = 0.4f;          // 駒の厚み

    vertices = // 頂点集合
    {   // 上面図と考えて指定
        // 前面
        {{-bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{ bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, UINT(id)}, // 右下
        {{-cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, UINT(id)}, // 左上
        {{ cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, UINT(id)}, // 右上
        {{ 0.0f,         height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, UINT(id)}, // 上    

        // 裏面
        {{-bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{ bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 右下
        {{-cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左上
        {{ cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 右上
        {{ 0.0f,         height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 上
    };

    piece->SetVertices(vertices);


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

    piece->SetIndices(indices);
 }

 // テクスチャ作成
void DX12::CreateTex()
{
    std::array<TexStruct::TexRGBA, 256*256> tex;

    int x = 0;
    int y = 0;
    for (auto& rgba : tex)
    {
        rgba.r =   x;
        rgba.g =   y / 256;
        rgba.b =   0;
        rgba.a = 255;

        x++;
        x %= 256;
        y++;
    }

    _tex->SetTex(tex);
 }




// コマンド実行
void DX12::ExeDX12()
{
    InitRenderTarget(); // レンダーターゲット初期処理
    ExeD3D(); // Direct3D処理実行
    ExeD2D(); // Direct2D処理実行
    PrepareRenderTargetToFlip(); // 画面フリップ準備処理
    _swapChain->Flip(); // 画面フリップ
}




// レンダーターゲット初期処理
void DX12::InitRenderTarget()
{
    // バックバッファインデックス取得
    _currentBackBuffIdx = _swapChain->GetCurrentBackBufferIdx();

    // バックバッファリソースをレンダーターゲットに変更
    auto resourceBarrier = _rb->GetRBToRenderTarget(_backBuffs[_currentBackBuffIdx]->GetBackBuff());
    _cmdList->SetResourceBarrier(resourceBarrier);

    // バックバッファをレンダーターゲットに設定
    auto rtvHandle = _rtvHeap->GetRTVHandle(_currentBackBuffIdx);
    auto dsvHandle = _dsvHeap->GetDSVHandle();
    _cmdList->SetRenderTarget(rtvHandle, dsvHandle);

    // クリア処理
    _cmdList->ClearRenderTarget(rtvHandle); // レンダーターゲットクリア
    _cmdList->ClearDepthStencil(dsvHandle); // デプスステンシルクリア
}




// Direct3D処理実行
void DX12::ExeD3D()
{
    Set3DCmd(); // 3Dコマンドセット

    // 将棋盤描画コマンドセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(_board.get()));
    SetDrawObjCmd(_board.get());

    // 駒描画コマンドセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(_pieces[0].get()));
    for (UINT i = 0; i < 2; i++)
    {
        SetDrawObjCmd(_pieces[i].get());
    }

    // ワールド行列、ビュープロジェクション行列をコンスタントバッファに書き込み
    _constBuff->WriteToConstBuff(
        _board.get(),
        _pieces,
        _viewMat.get(),
        _projMat.get());

    ExeCmd(); // コマンド実行
}

// 3Dコマンドセット
void DX12::Set3DCmd()
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
}

// オブジェクト描画コマンドセット
void DX12::SetDrawObjCmd(ShogiObj* shogiObj)
{
    // 頂点バッファビューセット
    _cmdList->SetVertBuffView(GetVertBuffView(shogiObj));
    // インデックス描画セット
    _cmdList->SetDrawWithIdx(shogiObj);
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertBuffView(ShogiObj* shogiObj)
{
    D3D12_VERTEX_BUFFER_VIEW view;

    view.BufferLocation =  // 頂点バッファのスタート位置
        shogiObj->GetVertAddress();
    view.StrideInBytes =   // 頂点1つ分のサイズ
        shogiObj->GetVertexByteSize();
        view.SizeInBytes = // 頂点全体のサイズ
        shogiObj->GetVerticesByteSize();

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIdxBuffView(ShogiObj* shogiObj)
{
    D3D12_INDEX_BUFFER_VIEW view;

    view.BufferLocation = // インデックスバッファのスタート位置
        shogiObj->GetIdxAddress();
    view.Format =         // フォーマット unsigned short
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =    // インデックス全体のサイズ
        shogiObj->GetIndicesByteSize();

    return view;
}

// コマンド実行
void DX12::ExeCmd()
{
    _cmdList->Close(); // コマンドクローズ
    _cmdQueue->ExeCmd(_cmdList.get()); // コマンド実行
    WaitProcessWithFence(); // フェンスによる同期処理
    _cmdAllocator->Reset();               // コマンドアロケータリセット
    _cmdList->Reset(_cmdAllocator.get()); // コマンドリストリセット
}



// Direct2D処理実行
void DX12::ExeD2D()
{
    StartD2D(); // Direct2D開始
    DrawStr(L"歩りゃあ", 0, 0, 720, 720);
    EndD2D(); // Direct2D終了
}

// Direct2D開始
void DX12::StartD2D()
{
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();

    _device11->AcquireWrappedBackBuffer(_wrappedBackBuffers[backBufferIdx].get());
    _d2dDeviceContext->SetRenderTarget(_d2dRenderTargets[backBufferIdx].get());
    _d2dDeviceContext->BeginDraw();
    _d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
}

// Direct2D終了
void DX12::EndD2D()
{
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();

    _d2dDeviceContext->EndDraw();
    _device11->ReleaseWrappedBackBuffer(_wrappedBackBuffers[backBufferIdx].get());
    _deviceContext->Flash(); // Direct2D描画
}

//// 文字を出力する
//void DX12::DrawStr(std::wstring str, D2D1_RECT_F rect)
//{
//    _d2dDeviceContext->DrawTextW(
//        str,
//        rect,
//        _dWriteTextFormat->GetDWriteTextFormat(),
//        _d2dSolidColorBrush->GetD2DSolidColorBrush());
//}
// 文字を出力する
void DX12::DrawStr(
    std::wstring str,
    float left,
    float top,
    float right,
    float bottom)
{
    D2D1_RECT_F rect = {left, top, right, bottom};

    _d2dDeviceContext->DrawTextW(
        str,
        rect,
        _dWriteTextFormat->GetDWriteTextFormat(),
        _d2dSolidColorBrush->GetD2DSolidColorBrush());
}




// レンダーターゲットのフリップ準備
void DX12::PrepareRenderTargetToFlip()
{
    // バックバッファを表示画面に設定
    auto resourceBarrier = _rb->GetRBToPresent(_backBuffs[_currentBackBuffIdx]->GetBackBuff());
    _cmdList->SetResourceBarrier(resourceBarrier);

    ExeCmd(); // コマンド実行
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
Piece* DX12::GetPawn(){return _pieces[0].get(); } // 歩を返す}
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

    _dWriteFactory = std::make_unique<DWriteFactory>();
    _device11      = std::make_unique<Device11>();
    _deviceContext = std::make_unique<DeviceContext>();
    _d2dDeviceContext = std::make_unique<D2DDeviceContext>();
    _d2dSolidColorBrush = std::make_unique<D2DSolidColorBrush>();
    _dWriteTextFormat = std::make_unique<DWriteTextFormat>();
    _pieceTextFormat = std::make_unique<DWriteTextFormat>();

    _cmdAllocator = std::make_unique<CmdAllocator>();
    _cmdList      = std::make_unique<CmdList>();
    _cmdQueue     = std::make_unique<CmdQueue>();

    _swapChain = std::make_unique<SwapChain>();

    _rtvHeap      = std::make_unique<RTVHeap>();

    _dsBuff  = std::make_unique<DSBuff>();
    _dsvHeap = std::make_unique<DSVHeap>();

    _fence = std::make_unique<Fence>();

    _viewport    = std::make_unique<Viewport>();
    _scissorRect = std::make_unique<ScissorRect>();

    _vShader       = std::make_unique<VShader>();
    _pShader       = std::make_unique<PShader>();
    _vertBuff      = std::make_unique<VertBuff>();
    _idxBuff       = std::make_unique<IdxBuff>();
    _constBuff     = std::make_unique<ConstBuff>();
    _texBuff       = std::make_unique<TexBuff>();
    _tex           = std::make_unique<Tex>();

    _csuHeap       = std::make_unique<CSUHeap>();
    _rootSignature = std::make_unique<RootSignature>();
    _inputLayout   = std::make_unique<InputLayout>();
    _pipeline      = std::make_unique<Pipeline>();

    _pieceTexRTVHeap = std::make_unique<RTVHeap>();
    _pieceTexSRVHeap = std::make_unique<CSUHeap>();

    _board = std::make_unique<Board>();

    _rb = std::make_unique<ResourceBarrier>();
}

DX12::~DX12(){}