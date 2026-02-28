#include"Draw.h"
#include<cassert>

ID3D12CommandAllocator** Draw::GetCommandAllocatorPtr(){return _commandAllocator.GetAddressOf(); }
ID3D12GraphicsCommandList** Draw::GetCommandListPtr(){return _commandList.GetAddressOf();}
ID3D12CommandQueue** Draw::GetCommandQueuePtr(){return _commandQueue.GetAddressOf(); }
IDXGISwapChain4** Draw::Draw::GetSwapChainPtr(){return _swapChain.GetAddressOf(); }
ID3D12Fence** Draw::GetFencePtr(){return _fence.GetAddressOf(); }
UINT Draw::GetFenceVal(){return _fenceVal;}

 HRESULT Draw::SetBufferToRTV(UINT i, ID3D12Resource** rtvPtr)
{
    return _swapChain->GetBuffer(i, IID_PPV_ARGS(rtvPtr));
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
        _bufferNum - 1,
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