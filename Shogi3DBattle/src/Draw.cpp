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
    if (FAILED(CreateSwapChainObj(arg.dxgiFactory, arg.hwnd, arg.width, arg.height)))
    {
        assert(false); return E_FAIL;
    }
    // ヒープオブジェクト作成
    if (FAILED(CreateHeapObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // RTV作成
    if (FAILED(_heap->CreateRTV(arg.device, _swapChain->GetSwapChain(), arg.buffNum)))
    {
        assert(false); return E_FAIL;
    }
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
HRESULT Draw::CreateHeapObj(ID3D12Device* device)
{
    //_heap = std::make_unique<RTVHeap>();
    _heap.reset(new RTVHeap());
    return _heap->CreateHeap(
        device,
        _swapChain->GetSwapChain(),
        _buffNum);
}




// レンダーターゲット準備
void Draw::PrepareRenderTarget(
    UINT rtvOffset,
    D3D12_RESOURCE_BARRIER resourceBarrier,
    ID3D12DescriptorHeap* dsvHeap)
{
    // バックバッファに対応するRTVをレンダーターゲットに設定
    auto backBufferIdx = _swapChain->GetSwapChain()->GetCurrentBackBufferIndex();
    auto rtvHandle = _heap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += backBufferIdx * rtvOffset;

    auto dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();

    ChangeRTVBarrierToRenderTarget(resourceBarrier);
    _commandList->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);
    // デプスステンシルバッファクリア
    _commandList->GetCommandList()->ClearDepthStencilView(
        dsvHandle,
        D3D12_CLEAR_FLAG_DEPTH,
        1.0f, 0, 0, nullptr);

    // レンダーターゲットクリア
    ClearRenderTarget(rtvHandle);
}

// RTVリソースをレンダーターゲットに変更
void Draw::ChangeRTVBarrierToRenderTarget(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    D3D12_RESOURCE_BARRIER barrier = resourceBarrier;

    auto backBufferIndex = _swapChain->GetSwapChain()->GetCurrentBackBufferIndex();
    auto rtv = _heap->GetRTV(backBufferIndex);

    barrier.Transition.pResource =
        rtv;
    barrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->GetCommandList()->ResourceBarrier(
        _buffNum - 1,
        &barrier);
}

// 画面クリア
void Draw::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    float clearRTVColor[] =
        {0.0f, 0.3f, 0.0f, 1.0f};
    _commandList->GetCommandList()->ClearRenderTargetView(
        handle, clearRTVColor, 0, nullptr);
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
    commandList->RSSetViewports(1, &arg.viewport);
    // シザー矩形セット
    commandList->RSSetScissorRects(1, &arg.scissorRect);
    // トポロジーセット
    commandList->IASetPrimitiveTopology(arg.topology);
    // 頂点バッファセット
    commandList->IASetVertexBuffers(0, 1, &arg.vertexBuffView);
    // インデックスバッファセット
    commandList->IASetIndexBuffer(&arg.indexBuffView);
    // 描画命令セット
    commandList->DrawIndexedInstanced(arg.vertexCount, arg.objCount, 0, 0, 0);
}




// 描画実行
void Draw::ExeDraw(DrawArg::ExeDrawArg arg)
{
    
    // バックバッファに対応するRTVを表示画面に設定
    ChangeRTVBarrierToPresent(arg.resourceBarrier);

    // コマンド実行
    ExeCommand();

    // 画面スワップ
    _swapChain->GetSwapChain()->Present(1, 0);

}

// RTVリソースを画面表示に変更
void Draw::ChangeRTVBarrierToPresent(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    D3D12_RESOURCE_BARRIER barrier = resourceBarrier;

    auto backBufferIndex = _swapChain->GetSwapChain()->GetCurrentBackBufferIndex();
    auto rtv = _heap->GetRTV(backBufferIndex);

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
    _commandList->GetCommandList()->Close();

    ID3D12CommandList* commandLists[] = {_commandList->GetCommandList()};
    _commandQueue->GetCommandQueue()->ExecuteCommandLists(1, commandLists);

    WaitProcessWithFence();

    ResetCommand();
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
    
    _heap->ClearRTV(); // RTV破棄
    if(FAILED(_swapChain->UpdateSwapChain( // スワップチェーン更新
        width, height)))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(_heap->CreateRTV( // RTV再作成
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