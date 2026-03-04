#include"Draw.h"
#include<cassert>

// 描画オブジェクト作成
HRESULT Draw::CreateDrawObject(
    DrawArgument::CreateDrawObjectArgument arg)
{
    // コマンドアロケータ作成
    if (FAILED(CreateCommandAllocator(
        arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // コマンドリスト作成
    if (FAILED(CreateCommandList(
        arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // コマンドキュー作成
    if (FAILED(CreateCommandQueue(
        arg.device, arg.commandQueueDesc)))
    {
        assert(false); return E_FAIL;
    }
    // スワップチェーン作成
    if (FAILED(CreateSwapChain(
        arg.dxgiFactory, arg.hwnd, arg.swapChainDesc)))
    {
        assert(false); return E_FAIL;
    }
    // フェンス作成
    if (FAILED(CreateFence(
        arg.device)))
    {
        assert(false); return E_FAIL;
    }
    // RTVヒープ作成
    if (FAILED(CreateRTVHeap(
        arg.device, arg.rtvHeapDesc)))
    {
        assert(false); return E_FAIL;
    }
    // RTV作成
    if (FAILED(CreateRTV(
        arg.device)))
    {
        assert(false); return E_FAIL;
    }
}

// コマンドアロケータ作成
HRESULT Draw::CreateCommandAllocator(ID3D12Device* device)
{
    return device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(_commandAllocator.ReleaseAndGetAddressOf()));
}

// コマンドリスト作成
HRESULT Draw::CreateCommandList(ID3D12Device* device)
{
    return device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        _commandAllocator.Get(),
        nullptr,
        IID_PPV_ARGS(_commandList.ReleaseAndGetAddressOf()));
}

// コマンドキュー作成
HRESULT Draw::CreateCommandQueue(
    ID3D12Device*            device,
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc)
{
    return device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(_commandQueue.ReleaseAndGetAddressOf()));
}

// スワップチェーン作成
HRESULT Draw::CreateSwapChain(
    IDXGIFactory6*        dxgiFactory,
    HWND                  hwnd,
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc)
{
    return dxgiFactory->CreateSwapChainForHwnd(
        _commandQueue.Get(),
        hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)_swapChain.ReleaseAndGetAddressOf());
}

// フェンス作成
HRESULT Draw::CreateFence(ID3D12Device* device)
{
    return device->CreateFence(
        _fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
}

// RTVヒープ作成
HRESULT Draw::CreateRTVHeap(
    ID3D12Device*              device,
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc)
{
    return device->CreateDescriptorHeap(
        &rtvHeapDesc,
        IID_PPV_ARGS(_rtvHeap.ReleaseAndGetAddressOf()));
}

// RTV作成
HRESULT Draw::CreateRTV(ID3D12Device* device)
{
    _rtvs.resize(_bufferCount);

    // ヒープの先頭アドレスを取得しておく
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle =
        _rtvHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < _bufferCount; i++)
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
    return _swapChain->GetBuffer(
        i, 
        IID_PPV_ARGS(_rtvs[i].ReleaseAndGetAddressOf()));
}




// レンダーターゲット準備
void Draw::PrepareRenderTarget(DrawArgument::PrepareRenderTargetArgument arg)
{
    // バックバッファに対応するRTVをレンダーターゲットに設定
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIndex();
    auto rtvHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += backBufferIdx * arg.rtvOffset;

    ChangeRTVBarrierToRenderTarget(arg.resourceBarrier);
    _commandList->OMSetRenderTargets(1, &rtvHandle, true, nullptr);

    // レンダーターゲットクリア
    ClearRenderTarget(rtvHandle);
}

// RTVリソースをレンダーターゲットに変更
void Draw::ChangeRTVBarrierToRenderTarget(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    D3D12_RESOURCE_BARRIER barrier = resourceBarrier;

    auto backBufferIdx = _swapChain->GetCurrentBackBufferIndex();

    barrier.Transition.pResource =
        _rtvs[backBufferIdx].Get();
    barrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->ResourceBarrier(
        _bufferCount - 1,
        &barrier);
}

// 画面クリア
void Draw::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    float clearRTVColor[] =
        {0.0f, 0.3f, 0.0f, 1.0f};
    _commandList->ClearRenderTargetView(
        handle, clearRTVColor, 0, nullptr);
}




// コマンドセット
void Draw::SetCommand(DrawArgument::SetCommandArgument arg)
{
    // パイプラインセット
    _commandList->SetPipelineState(arg.pipelineState);
    // ルートシグネチャセット
    _commandList->SetGraphicsRootSignature(arg.rootSignature);
    // テクスチャディスクリプタヒープセット
    _commandList->SetDescriptorHeaps(1, &arg.textureDescHeap);
    // ルートパラメータとディスクリプタヒープ関連付け
    _commandList->SetGraphicsRootDescriptorTable(
        0,
        arg.textureDescHeap->GetGPUDescriptorHandleForHeapStart());
    // ビューポートセット
    _commandList->RSSetViewports(1, &arg.viewport);
    // シザー矩形セット
    _commandList->RSSetScissorRects(1, &arg.scissorRect);
    // トポロジーセット
    _commandList->IASetPrimitiveTopology(arg.topology);
    // 頂点バッファセット
    _commandList->IASetVertexBuffers(0, 1, &arg.vertexBufferView);
    // インデックスバッファセット
    _commandList->IASetIndexBuffer(&arg.indexBufferView);
    // 描画命令セット
    _commandList->DrawIndexedInstanced(arg.vertexCount, arg.objectCount, 0, 0, 0);

}




// 描画実行
void Draw::ExecuteDraw(DrawArgument::ExecuteDrawArgument arg)
{
    // バックバッファに対応するRTVを表示画面に設定
    ChangeRTVBarrierToPresent(arg.resourceBarrier);

    // コマンド実行および画面スワップによる表示
    _commandList->Close();
    ExecuteCommand();
    WaitProcessWithFence();
    ResetCommand();
    _swapChain->Present(1, 0);

}

// RTVリソースを画面表示に変更
void Draw::ChangeRTVBarrierToPresent(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    D3D12_RESOURCE_BARRIER barrier = resourceBarrier;

    auto backBufferIdx = _swapChain->GetCurrentBackBufferIndex();

    barrier.Transition.pResource =
        _rtvs[backBufferIdx].Get();
    barrier.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _commandList->ResourceBarrier(
        _bufferCount - 1,
        &barrier);
}

// コマンド実行
void Draw::ExecuteCommand()
{
    ID3D12CommandList* commandLists[] = {_commandList.Get()};
    _commandQueue->ExecuteCommandLists(1, commandLists);
}

// フェンスによる同期制御
void Draw::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _commandQueue->Signal(_fence.Get(), ++_fenceVal);

    while (_fence->GetCompletedValue() != _fenceVal)
    {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        _fence->SetEventOnCompletion(_fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}

// コマンドリセット
void Draw::ResetCommand()
{
    _commandAllocator->Reset();
    _commandList->Reset(_commandAllocator.Get(), nullptr);
}




Draw::Draw(UINT bufferNum)
{
    _bufferCount = bufferNum;
}

Draw::~Draw(){}