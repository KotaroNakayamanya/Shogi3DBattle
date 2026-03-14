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


// DirectX12オブジェクト作成
bool DX12::CreateDX12Obj(GameWindow* gameWindow)
{
    // ファクトリー系作成
    if (FAILED(CreateDXGIFactory())) goto failed; // DXGIファクトリー作成
    if (FAILED(_dxgiFactory->CreateAdapter(_adapter.get()))) goto failed; // アダプター作成
    if (FAILED(_dxgiFactory->CreateDevice(_device.get(), _adapter.get()))) goto failed; // デバイス作成
    _adapter.reset(); // アダプター破棄

    // コマンド作成
    if (FAILED(_device->CreateComAllocator(_comAllocator.get()))) goto failed; // コマンドアロケータ作成
    if (FAILED(_device->CreateComList(_comList.get(), _comAllocator.get()))) goto failed; // コマンドリスト作成
    if (FAILED(_device->CreateComQueue(_comQueue.get()))) goto failed; // コマンドキュー作成

    // スワップチェーン作成
    if (FAILED(_dxgiFactory->CreateSwapChain(_swapChain.get(), _comQueue.get(), gameWindow))) goto failed;
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
    
    if (FAILED(CreateVertexSets())) goto failed; // 頂点集合作成

    // 頂点・インデックスバッファ作成
    if (FAILED(_device->CreateVertBuff(_vertBuff.get(), _pawn->GetVerticesByteSize()))) goto failed; // 頂点バッファ作成
    if (FAILED(_device->CreateIdxBuff (_idxBuff.get(),  _pawn->GetVerticesByteSize()))) goto failed; // インデックスバッファ作成
    if (FAILED(_vertBuff->WriteVertBuff(_pawn->GetVerticesPtr()))) goto failed; // 頂点バッファに書き込み
    if (FAILED(_idxBuff ->WriteIdxBuff (_pawn->GetIndicesPtr())))  goto failed; // インデックスバッファに書き込み
    _device->CreateInputLayout(_inputLayout.get()); // 入力レイアウト（頂点バッファの中身の内訳）作成

    // テクスチャバッファ作成
    if (FAILED(_device->CreateTexBuff(_texBuff.get()))) goto failed; // テクスチャバッファ作成

    // コンスタントバッファ（頂点の変換行列を格納するバッファ）作成
    if (FAILED(_device->CreateConstBuff(_constBuff.get(), _pawn->GetVerticesByteSize()))) goto failed; // コンスタントバッファ作成
    if (FAILED(_constBuffMap->MapConstBuff(_constBuff->GetBuff()))) goto failed; // コンスタントバッファをマップ

    // CBV, SRV作成
    if (FAILED(_device->CreateCSUHeap(_csuHeap.get()))) goto failed; // CSUヒープオブジェクト作成
    _device->CreateCBV(_cbv.get(), _csuHeap.get(), _constBuff.get()); // CBV作成
    _device->CreateSRV(_srv.get(), _csuHeap.get(), _texBuff.get());   // SRV作成

    
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

// 頂点集合作成
HRESULT DX12::CreateVertexSets()
{

    /*std::for_each(_objects.begin(), _objects.end(),
        [](std::unique_ptr<Object>& object)
        {
            object = std::make_unique<Object>();
        });*/
    _pawn = std::make_unique<Pawn>();

    return S_OK;
}




// コマンド実行
void DX12::ExeDX12()
{
    // レンダーターゲットの準備をする
    PrepareRenderTarget();

    // 頂点を変換
    _constBuffMap->WriteMat(
        _pawn->GetWorldMat(),
        _viewMat->GetViewMat(),
        _projMat->GetProjMat());

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
    _comList->SetRenderTarget(rtvHandle, dsvHandle);

    // レンダーターゲットクリア
    _comList->ClearRenderTarget(rtvHandle);
     // デプスステンシルクリア
    _comList->ClearDepthStencil(dsvHandle); 
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

    _comList->SetResourceBarrier(resourceBarrier);
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
    //DrawArg::SetCommandArg arg =
    //    GetSetCommandArg();

    //_draw->SetCommand(arg);

    //ID3D12GraphicsCommandList* commandList =
    //_commandList->GetCommandList();

    // パイプラインセット
    _comList->SetPipeline(_pipeline->GetPipelineState());

    // ルートシグネチャセット
    _comList->SetRootSignature(_rootSignature->GetRootSignature());

    // CBV,SRVヒープセット
    ID3D12DescriptorHeap* csuHeaps[] = {_csuHeap->GetCSUHeap()};
    _comList->SetCSUHeaps(csuHeaps); 
    // ルートパラメータとディスクリプタヒープ関連付け
    //auto csuHandle = arg.csuHeap->GetGPUDescriptorHandleForHeapStart();
    _comList->SetDescriptorTable(0, _cbv->GetCBVHandle()); // CBV
    //_comList->
    //csuHandle.ptr += arg.offset;
    _comList->SetDescriptorTable(1, _srv->GetSRVHandle()); // SRV

    // ビューポートセット
    D3D12_VIEWPORT viewports[] = {_viewport->GetViewport()};
    _comList->SetViewports(viewports);
    //_comList->RSSetViewports(1, viewports);

    // シザー矩形セット
    D3D12_RECT scissorRects[] = {_scissorRect->GetScissorRect()};
    _comList->SetScissorRects(scissorRects);

    // トポロジーセット
    //_comList->IASetPrimitiveTopology(arg.topology);
    _comList->SetTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    // 頂点バッファビューセット
    //commandList->IASetVertexBuffers(0, 1, &arg.vertexBuffView);
    D3D12_VERTEX_BUFFER_VIEW vertBuffViews[] = {GetVertexBuffView()};
    _comList->SetVertBuffViews(vertBuffViews);
    // インデックスバッファセット
    _comList->SetIdxBuffView(GetIndexBuffView());
    // インデックス描画セット
    //commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);
    _comList->SetDrawWithIdx(_pawn.get());



    ////////////
    //D3D12_VIEWPORT aaa = arg.viewport;
    //aaa.Width = 300;
    //commandList->RSSetViewports(1, &aaa);
    //commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);
    //aaa.Width = 700;
    //commandList->RSSetViewports(1, &aaa);
    //commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);

}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertexBuffView()
{
    D3D12_VERTEX_BUFFER_VIEW view;

    ComPtr<ID3D12Resource> vertexBuff =
        _vertBuff->GetVertBuff();

    UINT vertexByteSize   = _pawn->GetVertexByteSize();
    UINT verticesByteSize = _pawn->GetVerticesByteSize();

    view.BufferLocation =
        vertexBuff->GetGPUVirtualAddress();
    view.SizeInBytes =
        verticesByteSize; // 注意
    view.StrideInBytes =
        vertexByteSize; // 注意

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIndexBuffView()
{
    D3D12_INDEX_BUFFER_VIEW view;

    ComPtr<ID3D12Resource> indexBuff =
        _idxBuff->GetIdxBuff();

    UINT indicesByte = _pawn->GetIndicesByteSize();

    view.BufferLocation =
        indexBuff->GetGPUVirtualAddress();
    view.Format =
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =
        indicesByte;

    return view;
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

    _comList->SetResourceBarrier(barrier);
}




// コマンド実行
void DX12::ExeCommand()
{
    _comList->GetComList()->Close(); // コマンドクローズ

    ID3D12CommandList* commandLists[] = {_comList->GetComList()}; // リストに格納
    UINT listNum = sizeof(commandLists) / sizeof(ID3D12CommandList); // リスト数取得

    _comQueue->GetComQueue()->ExecuteCommandLists(listNum, commandLists); // コマンドキュー実行

    WaitProcessWithFence(); // フェンスによる同期処理

    ResetCommand(); // コマンドリセット
}

// フェンスによる同期制御
void DX12::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _comQueue->GetComQueue()->Signal(_fence->GetFence(), _fence->GetIncrementFenceVal());

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
        _comAllocator->GetCommandAllocator();

    commandAllocator->Reset();
    _comList->GetComList()->Reset(commandAllocator, nullptr);
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

    _comAllocator = std::make_unique<ComAllocator>();
    _comList      = std::make_unique<ComList>();
    _comQueue     = std::make_unique<ComQueue>();

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
    _constBuffMap  = std::make_unique<ConstBuffMap>();
    _csuHeap       = std::make_unique<CSUHeap>();
    _cbv           = std::make_unique<CBV>();
    _srv           = std::make_unique<SRV>();
    _rootSignature = std::make_unique<RootSignature>();
    _inputLayout   = std::make_unique<InputLayout>();
    _pipeline      = std::make_unique<Pipeline>();
}

DX12::~DX12(){}