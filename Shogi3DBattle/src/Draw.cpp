#include"Draw.h"
#include<cassert>

// 描画オブジェクト作成
HRESULT Draw::CreateDrawObj(DrawArg::CreateDrawObjArg arg)
{
    // コマンドアロケータオブジェクト作成
    if (FAILED(CreateCommandAllocatorObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // コマンドリストオブジェクト作成
    if (FAILED(CreateCommandListObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // コマンドキューオブジェクト作成
    if (FAILED(CreateCommandQueueObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // フェンスオブジェクト作成
    if (FAILED(CreateFenceObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }

    // スワップチェーンオブジェクト作成
    if (FAILED(CreateSwapChainObj(arg.dxgiFactory, arg.hwnd, arg.windowWidth, arg.windowHeight)))
    {
        assert(false); return E_FAIL;
    }
    // RTVヒープオブジェクト作成
    if (FAILED(CreateRTVHeapObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // RTV作成
    if (FAILED(_rtvHeap->CreateRTV(arg.device, _swapChain->GetSwapChain(), arg.buffNum)))
    {
        assert(false); return E_FAIL;
    }

    // デプスステンシルバッファオブジェクト作成
    if (FAILED(CreateDSBuffObj(arg.device, arg.windowWidth, arg.windowHeight)))
    {
        assert(false); return false;
    }
    // DSVヒープオブジェクト作成
    if (FAILED(CreateDSVHeapObj(arg.device)))
    {
        assert(false); return false;
    }

    // ビューポート作成
    CreateViewports(arg.windowWidth, arg.windowHeight);
    // シザー矩形作成
    CreateScissorRects(arg.windowWidth, arg.windowHeight);
    // RTVバイト数取得
    _rtvOffset = arg.device->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    return S_OK;
}

// コマンドアロケータオブジェクト作成
HRESULT Draw::CreateCommandAllocatorObj(ID3D12Device* device)
{
    _commandAllocator = std::make_unique<CommandAllocator>();
    return _commandAllocator->CreateCommandAllocator(device);
}

// コマンドリストオブジェクト作成
HRESULT Draw::CreateCommandListObj(ID3D12Device* device)
{
    _commandList = std::make_unique<CommandList>();
    return _commandList->CreateCommandList(
        device, _commandAllocator->GetCommandAllocator());
}
// コマンドキューオブジェクト作成
HRESULT Draw::CreateCommandQueueObj(ID3D12Device* device)
{
    _commandQueue = std::make_unique<CommandQueue>();
    return _commandQueue->CreateCommandQueue(device);
}

// スワップチェーンオブジェクト作成
HRESULT Draw::CreateSwapChainObj(
    IDXGIFactory6* dxgiFactory,
    HWND hwnd,
    UINT width,
    UINT height)
{
    ID3D12CommandQueue* commandQueue =
        _commandQueue->GetCommandQueue();

    DrawArg::CreateSwapChainArg arg =
        GetCreateSwapChainArg(dxgiFactory, commandQueue, hwnd, width, height);

    //_swapChain = std::make_unique<SwapChain>();
    _swapChain.reset(new SwapChain());
    return _swapChain->CreateSwapChain(arg);
}

// スワップチェーン作成用引数
DrawArg::CreateSwapChainArg Draw::GetCreateSwapChainArg(
    IDXGIFactory6* dxgiFactory,
    ID3D12CommandQueue* commandQueue,
    HWND hwnd,
    UINT width,
    UINT height)
{
    DrawArg::CreateSwapChainArg arg = {};

    arg.dxgiFactory = dxgiFactory;
    arg.commandQueue = commandQueue;
    arg.hwnd = hwnd,
    arg.width = width;
    arg.height = height;
    arg.buffNum = _buffNum;

    return arg;
}

// フェンスオブジェクト作成
HRESULT Draw::CreateFenceObj(ID3D12Device* device)
{
    _fence = std::make_unique<Fence>();
    return _fence->CreateFence(device);
}

// ヒープオブジェクト作成
HRESULT Draw::CreateRTVHeapObj(ID3D12Device* device)
{
    //_heap = std::make_unique<RTVHeap>();
    _rtvHeap.reset(new RTVHeap());
    return _rtvHeap->CreateHeap(
        device,
        _swapChain->GetSwapChain(),
        _buffNum);
}

// デプスステンシルバッファ作成
HRESULT Draw::CreateDSBuffObj(
    ID3D12Device* device,
    UINT windowWidth,
    UINT windowHeight)
{
    _dsBuff = std::make_unique<DSBuff>();
    return _dsBuff->CreateDSBuffObj(
        device, windowWidth, windowHeight);
}

// DSVヒープ作成
HRESULT Draw::CreateDSVHeapObj(
    ID3D12Device* device)
{
    _dsvHeap = std::make_unique<DSVHeap>();
    return _dsvHeap->CreateDSVHeap(
        device, _dsBuff->GetDSBuff());
}

// ビューポート作成
void Draw::CreateViewports(UINT windowWidth, UINT windowHeight)
{
    _viewport.Width    = windowWidth;  // 横
    _viewport.Height   = windowHeight; // 縦
    _viewport.TopLeftX = 0; // 左上横位置
    _viewport.TopLeftY = 0; // 左上縦位置
    _viewport.MaxDepth = 1.0f; // 深度最大値
    _viewport.MinDepth = 0.0f; // 深度最小値
}

// シザー矩形作成
void Draw::CreateScissorRects(UINT windowWidth, UINT windowHeight)
{
    _scissorRect.left = 0;              // 左
    _scissorRect.right = windowWidth;   // 右
    _scissorRect.top = 0;               // 上
    _scissorRect.bottom = windowHeight; // 下
}

// リソースバリア基本設定作成
void Draw::CreateBasiceResourceBarrier()
{
    _basicResourceBarrier.Type =
        D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    _basicResourceBarrier.Flags =
        D3D12_RESOURCE_BARRIER_FLAG_NONE;
    _basicResourceBarrier.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
}




// レンダーターゲット準備
void Draw::PrepareRenderTarget()
{
    // バックバッファインデックス取得
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();

    // ハンドル取得
    auto rtvHandle = _rtvHeap->GetRTVStartHandle();
    //auto dsvHandle = _dsvHeap->GetCPUDescriptorHandleForHeapStart();
    auto dsvHandle = _dsvHeap->GetDSVStartHandle();
    rtvHandle.ptr += backBufferIdx * _rtvOffset;

    // RTVをレンダーターゲットに変更
    ChangeRTVBarrierToRenderTarget(backBufferIdx);

     // バックバッファをレンダーターゲットに設定
    _commandList->SetRenderTarget(rtvHandle, dsvHandle);

    // レンダーターゲットクリア
    _commandList->ClearRenderTarget(rtvHandle);
     // デプスステンシルクリア
    _commandList->ClearDepthStencil(dsvHandle); 
}

// RTVリソースをレンダーターゲットに変更
void Draw::ChangeRTVBarrierToRenderTarget(UINT backBufferIdx)
{
    D3D12_RESOURCE_BARRIER resourceBarrier = _basicResourceBarrier;

    auto rtv = _rtvHeap->GetRTV(backBufferIdx);

    resourceBarrier.Transition.pResource =
        rtv;
    resourceBarrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    resourceBarrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->SetResourceBarrier(resourceBarrier);
}





// コマンドセット
void Draw::SetCommand(DrawArg::SetCommandArg arg)
{
    ID3D12GraphicsCommandList* commandList =
        _commandList->GetCommandList();

    // パイプラインセット
    commandList->SetPipelineState(arg.pipelineState);
    // ルートシグネチャセット
    commandList->SetGraphicsRootSignature(arg.rootSignature);
    // CBV,SRVヒープセット
    commandList->SetDescriptorHeaps(1, &arg.heap);
    // ルートパラメータとディスクリプタヒープ関連付け
    auto handle = arg.heap->GetGPUDescriptorHandleForHeapStart();
    commandList->SetGraphicsRootDescriptorTable(
        0,
        handle);
    handle.ptr += arg.offset;
    commandList->SetGraphicsRootDescriptorTable(
        1,
        handle);
    // ビューポートセット
    commandList->RSSetViewports(1, &_viewport);
    // シザー矩形セット
    commandList->RSSetScissorRects(1, &_scissorRect);
    // トポロジーセット
    commandList->IASetPrimitiveTopology(arg.topology);
    // 頂点バッファセット
    commandList->IASetVertexBuffers(0, 1, &arg.vertexBuffView);
    // インデックスバッファセット
    commandList->IASetIndexBuffer(&arg.indexBuffView);
    // 描画命令セット
    commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);



    ////////////
    //D3D12_VIEWPORT aaa = arg.viewport;
    //aaa.Width = 300;
    //commandList->RSSetViewports(1, &aaa);
    //commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);
    //aaa.Width = 700;
    //commandList->RSSetViewports(1, &aaa);
    //commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);
}




// 描画実行
void Draw::ExeDraw()
{
     // バックバッファインデックス取得
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();
    
    
    ChangeRTVBarrierToPresent(backBufferIdx); // RTVを表示画面に設定
    ExeCommand(); // コマンド実行
    _swapChain->Flip(); // 画面フリップ

}

// RTVリソースを画面表示に変更
void Draw::ChangeRTVBarrierToPresent(UINT backBufferIdx)
{
    D3D12_RESOURCE_BARRIER barrier = _basicResourceBarrier;;

    auto rtv = _rtvHeap->GetRTV(backBufferIdx);

    barrier.Transition.pResource =
        rtv;
    barrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _commandList->GetCommandList()->ResourceBarrier(
        _buffNum - 1,
        &barrier);
}




// コマンド実行
void Draw::ExeCommand()
{
    _commandList->GetCommandList()->Close(); // コマンドクローズ

    ID3D12CommandList* commandLists[] = {_commandList->GetCommandList()}; // リストに格納
    UINT listNum = sizeof(commandLists) / sizeof(ID3D12CommandList); // リスト数取得

    _commandQueue->GetCommandQueue()->ExecuteCommandLists(listNum, commandLists); // コマンドキュー実行

    WaitProcessWithFence(); // フェンスによる同期処理

    ResetCommand(); // コマンドリセット
}

// フェンスによる同期制御
void Draw::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _commandQueue->GetCommandQueue()->Signal(_fence->GetFence(), _fence->GetIncrementFenceVal());

    while (_fence->GetFence()->GetCompletedValue() != _fence->GetFenceVal())
    {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        _fence->GetFence()->SetEventOnCompletion(_fence->GetFenceVal(), event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}

// コマンドリセット
void Draw::ResetCommand()
{
    ID3D12CommandAllocator* commandAllocator =
        _commandAllocator->GetCommandAllocator();

    commandAllocator->Reset();
    _commandList->GetCommandList()->Reset(commandAllocator, nullptr);
}




// 描画設定更新
HRESULT Draw::UpdateDrawConf(
    ID3D12Device* device,
    UINT width, 
    UINT height,
    UINT buffNum)
{
    WaitProcessWithFence(); // GPUが処理中であれば待つ
    
    _rtvHeap->ClearRTV(); // RTV破棄
    if(FAILED(_swapChain->UpdateSwapChain( // スワップチェーン更新
        width, height)))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(_rtvHeap->CreateRTV( // RTV再作成
        device, _swapChain->GetSwapChain(), buffNum)))
    {
        assert(false); return E_FAIL;
    }

    return S_OK;
}



Draw::Draw(UINT buffNum) : Draw()
{
    _buffNum = buffNum;
}

Draw::Draw(){}
Draw::~Draw(){}