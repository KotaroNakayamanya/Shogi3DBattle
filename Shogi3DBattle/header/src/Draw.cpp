#include"Draw.h"
#include<cassert>

HRESULT Draw::CreateDrawObject(
    ID3D12Device*  device,
    IDXGIFactory6* dxgiFactory,
    HWND           hwnd)
{
    if (FAILED(CreateCommandAllocator(device)))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateCommandList(device)))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateCommandQueue(device)))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateSwapChain(dxgiFactory, hwnd)))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateFence(device)))
    {
        assert(false); return E_FAIL;
    }
}

HRESULT Draw::CreateCommandAllocator(ID3D12Device* device)
{
    return device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(_commandAllocator.ReleaseAndGetAddressOf()));
}

HRESULT Draw::CreateCommandList(ID3D12Device* device)
{
    return device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        _commandAllocator.Get(),
        nullptr,
        IID_PPV_ARGS(_commandList.ReleaseAndGetAddressOf()));
}

HRESULT Draw::CreateCommandQueue(ID3D12Device* device)
{
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc =
        GetCommandQueueDesc();

    return device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(_commandQueue.ReleaseAndGetAddressOf()));
}

D3D12_COMMAND_QUEUE_DESC Draw::GetCommandQueueDesc()
{
    D3D12_COMMAND_QUEUE_DESC desc;
    desc.Type =    // コマンドリストタイプの種類
        D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = // アプリケーション優先度 通常
        D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = // タイムアウトなし
        D3D12_COMMAND_QUEUE_FLAG_NONE; 
    desc.NodeMask =
        0;

    return desc;
}

HRESULT Draw::CreateSwapChain(IDXGIFactory6* dxgiFactory, HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc();

    return dxgiFactory->CreateSwapChainForHwnd(
        _commandQueue.Get(),
        hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)_swapChain.ReleaseAndGetAddressOf());
}

DXGI_SWAP_CHAIN_DESC1 Draw::GetSwapChainDesc()
{
    DXGI_SWAP_CHAIN_DESC1 desc;

    desc.Width =
        300;
    desc.Height =
        500;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo =
        false;
    desc.SampleDesc.Count =
        1;
    desc.SampleDesc.Quality =
        0;
    desc.BufferUsage =
        DXGI_USAGE_BACK_BUFFER;
    desc.BufferCount =
        _bufferNum;

    desc.Scaling =
        DXGI_SCALING_STRETCH;
    desc.SwapEffect =
        DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode =
        DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags =
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    return desc;
}

HRESULT Draw::CreateFence(ID3D12Device* device)
{
    return device->CreateFence(
        _fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
}

HRESULT Draw::SetBufferToRTV(UINT i, ID3D12Resource** rtvPtr)
{
    return _swapChain->GetBuffer(i, IID_PPV_ARGS(rtvPtr));
}




//ID3D12CommandQueue* Draw::GetCommandQueue()
//{
//    return _commandQueue.Get();
//}

void Draw::ChangeRTVToRenderTarget(ID3D12Resource* rtv)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(rtv);

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->ResourceBarrier(
        _bufferNum - 1,
        &bufferBarrierDesc);
}

void Draw::ChangeRTVToPresent(ID3D12Resource* rtv)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(rtv);

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _commandList->ResourceBarrier(
        _bufferNum - 1,
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

UINT Draw::GetBackBufferIdx()
{
    return _swapChain->GetCurrentBackBufferIndex();
}

void Draw::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    float clearRTVColor[] =
        {1.0f, 1.0f, 0.0f, 1.0f};
    _commandList->ClearRenderTargetView(
        handle, clearRTVColor, 0, nullptr);
}

void Draw::CloseCommand()
{
    _commandList->Close();
}

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

void Draw::ResetCommand()
{
    _commandAllocator->Reset();
    _commandList->Reset(_commandAllocator.Get(), nullptr);
}

void Draw::DisplaySwap()
{
    _swapChain->Present(1, 0);
}




Draw::Draw(UINT bufferNum)
{
    _bufferNum = bufferNum;
}