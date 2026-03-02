#include"Draw.h"
#include<cassert>

// 描画オブジェクト作成
HRESULT Draw::CreateDrawObject(
    ID3D12Device*              device,
    IDXGIFactory6*             dxgiFactory,
    HWND                       hwnd,
    D3D12_COMMAND_QUEUE_DESC   commandQueueDesc,
    DXGI_SWAP_CHAIN_DESC1      swapChainDesc,
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc)
{
    // コマンドアロケータ作成
    if (FAILED(CreateCommandAllocator(
        device)))
    {
        assert(false); return E_FAIL;
    }
    // コマンドリスト作成
    if (FAILED(CreateCommandList(
        device)))
    {
        assert(false); return E_FAIL;
    }
    // コマンドキュー作成
    if (FAILED(CreateCommandQueue(
        device, commandQueueDesc)))
    {
        assert(false); return E_FAIL;
    }
    // スワップチェーン作成
    if (FAILED(CreateSwapChain(
        dxgiFactory, hwnd, swapChainDesc)))
    {
        assert(false); return E_FAIL;
    }
    // フェンス作成
    if (FAILED(CreateFence(
        device)))
    {
        assert(false); return E_FAIL;
    }
    // RTVヒープ作成
    if (FAILED(CreateRTVHeap(
        device, rtvHeapDesc)))
    {
        assert(false); return E_FAIL;
    }
    // RTV作成
    if (FAILED(CreateRTV(
        device)))
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
void Draw::PrepareRenderTarget(UINT rtvOffset)
{
    // バックバッファのハンドルを取得
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIndex();
    auto rtvHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += backBufferIdx * rtvOffset;

    // バックバッファに対応するRTVをレンダーターゲットに設定
    ChangeRTVBarrierToRenderTarget(_rtvs[backBufferIdx].Get());
    SetRenderTarget(rtvHandle);

    // レンダーターゲットクリア
    ClearRenderTarget(rtvHandle);
}

// 描画実行
void Draw::ExecuteDraw()
{
    // バックバッファに対応するRTVを表示画面に設定
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIndex();
    ChangeRTVBarrierToPresent(_rtvs[backBufferIdx].Get());

    // コマンド実行および画面スワップによる表示
    _commandList->Close();
    ExecuteCommand();
    WaitProcessWithFence();
    ResetCommand();
    _swapChain->Present(1, 0);
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

void Draw::ChangeRTVBarrierToRenderTarget(ID3D12Resource* rtv)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(rtv);

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->ResourceBarrier(
        _bufferCount - 1,
        &bufferBarrierDesc);
}

void Draw::ChangeRTVBarrierToPresent(ID3D12Resource* rtv)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(rtv);

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _commandList->ResourceBarrier(
        _bufferCount - 1,
        &bufferBarrierDesc);
}

D3D12_RESOURCE_BARRIER Draw::GetBufferBarrierDesc(
    ID3D12Resource* rtv)
{
    D3D12_RESOURCE_BARRIER desc;

    desc.Type =
        D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    desc.Flags =
        D3D12_RESOURCE_BARRIER_FLAG_NONE;

    desc.Transition.pResource =
        rtv;
    desc.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    return desc;  
}

void Draw::SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    _commandList->OMSetRenderTargets(1, &handle, true, nullptr);
}

void Draw::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    float clearRTVColor[] =
        {1.0f, 1.0f, 0.0f, 1.0f};
    _commandList->ClearRenderTargetView(
        handle, clearRTVColor, 0, nullptr);
}





// パイプラインセット
void Draw::SetPipeLineState(ID3D12PipelineState* pipelineState)
{
    _commandList->SetPipelineState(pipelineState);
}

// ルートシグネチャセット
void Draw::SetRootSignature(ID3D12RootSignature* rootSignature)
{
    _commandList->SetGraphicsRootSignature(rootSignature);
}

// ビューポートセット
void Draw::SetViewports(D3D12_VIEWPORT viewport)
{
    _commandList->RSSetViewports(1, &viewport);
}

// シザー矩形セット
void Draw::SetScissorRects(D3D12_RECT scissorRect)
{
    _commandList->RSSetScissorRects(1, &scissorRect);
}

// プリミティブトポロジーセット
void Draw::SetPremitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
{
    _commandList->IASetPrimitiveTopology(topology);
}

// 頂点バッファをコマンドリストへセット
void Draw::SetVertexBuffers(
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView)
{
    _commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
}

// インデックスバッファをコマンドリストへセット
void Draw::SetIndexBuffer(
    D3D12_INDEX_BUFFER_VIEW indexBufferView)
{
    _commandList->IASetIndexBuffer(&indexBufferView);
}

// 描画命令セット
void Draw::SetDrawInstanced(UINT vertexCount, UINT objectCount)
{
    _commandList->DrawIndexedInstanced(vertexCount, objectCount, 0, 0, 0);
}


Draw::Draw(UINT bufferNum)
{
    _bufferCount = bufferNum;
}