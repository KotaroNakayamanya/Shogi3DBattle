#include"Draw.h"
#include<cassert>

#include"CommandAllocator.h"
#include"CommandList.h"
#include"CommandQueue.h"
#include"SwapChain.h"
#include"Fence.h"

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
    // スワップチェーンオブジェクト作成
    if (FAILED(CreateSwapChainObj(arg.dxgiFactory, arg.hwnd)))
    {
        assert(false); return E_FAIL;
    }
    // フェンスオブジェクト作成
    if (FAILED(CreateFenceObj(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // RTVヒープ作成
    if (FAILED(CreateRTVHeap(arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // RTV作成
    if (FAILED(CreateRTV(arg.device)))
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
    HWND hwnd)
{
    ID3D12CommandQueue* commandQueue =
        _commandQueue->GetCommandQueue();
    
    _swapChain = std::make_unique<SwapChain>();
    return _swapChain->CreateSwapChain(
        dxgiFactory, commandQueue, hwnd, _buffNum);
}

// フェンスオブジェクト作成
HRESULT Draw::CreateFenceObj(ID3D12Device* device)
{
    _fence = std::make_unique<Fence>();
    return _fence->CreateFence(device);
}

// RTVヒープ作成
HRESULT Draw::CreateRTVHeap(ID3D12Device* device)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetHeapDesc();

    return device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_rtvHeap.ReleaseAndGetAddressOf()));
}

// RTV作成
HRESULT Draw::CreateRTV(ID3D12Device* device)
{
    _rtvs.resize(_buffNum);

    // ヒープの先頭アドレスを取得しておく
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle =
        _rtvHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < _buffNum; i++)
    {
        if (FAILED(SetRTVBuffer(i))) // 各RTVにバッファを対応させる
        {
            assert(false); return E_FAIL;
        }

        device->CreateRenderTargetView(
            _rtvs[i].Get(),
            nullptr,
            rtvHeapHandle);

        // RTVビューを入れた分、アドレスを足す
        rtvHeapHandle.ptr +=
            device->GetDescriptorHandleIncrementSize(
                D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    return S_OK;
}

// RTVにバッファを対応させる
 HRESULT Draw::SetRTVBuffer(UINT i)
{
    return _swapChain->GetSwapChain()->GetBuffer(
        i, 
        IID_PPV_ARGS(_rtvs[i].ReleaseAndGetAddressOf()));
}




// レンダーターゲット準備
void Draw::PrepareRenderTarget(DrawArg::PrepareRenderTargetArg arg)
{
    // バックバッファに対応するRTVをレンダーターゲットに設定
    auto backBufferIdx = _swapChain->GetSwapChain()->GetCurrentBackBufferIndex();
    auto rtvHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += backBufferIdx * arg.rtvOffset;

    ChangeRTVBarrierToRenderTarget(arg.resourceBarrier);
    _commandList->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, true, nullptr);

    // レンダーターゲットクリア
    ClearRenderTarget(rtvHandle);
}

// RTVリソースをレンダーターゲットに変更
void Draw::ChangeRTVBarrierToRenderTarget(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    D3D12_RESOURCE_BARRIER barrier = resourceBarrier;

    auto backBufferIdx = _swapChain->GetSwapChain()->GetCurrentBackBufferIndex();

    barrier.Transition.pResource =
        _rtvs[backBufferIdx].Get();
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
    // ディスクリプタヒープセット
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
    _commandList->GetCommandList()->Close();
    ExeCommand();
    WaitProcessWithFence();
    ResetCommand();

    // 画面スワップ
    _swapChain->GetSwapChain()->Present(1, 0);

}

// RTVリソースを画面表示に変更
void Draw::ChangeRTVBarrierToPresent(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    D3D12_RESOURCE_BARRIER barrier = resourceBarrier;

    auto backBufferIdx = _swapChain->GetSwapChain()->GetCurrentBackBufferIndex();

    barrier.Transition.pResource =
        _rtvs[backBufferIdx].Get();
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
    ID3D12CommandList* commandLists[] = {_commandList->GetCommandList()};
    _commandQueue->GetCommandQueue()->ExecuteCommandLists(1, commandLists);
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

// ヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC Draw::GetHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        _buffNum;
    desc.Flags =
        D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return desc;
}




Draw::Draw(UINT bufferNum)
{
    _buffNum = bufferNum;
}

Draw::~Draw(){}