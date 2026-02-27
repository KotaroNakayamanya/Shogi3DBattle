#include"Command.h"
#include<cassert>

ID3D12CommandQueue* Command::GetCommandQueue()
{
    return _commandQueue.Get();
}

HRESULT Command::CreateCommandObject(
    ID3D12Device* device)
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
}

void Command::ChangeRTVToRenderTarget(ID3D12Resource* rtv, UINT backBufferNum)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(rtv);

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->ResourceBarrier(
        backBufferNum,
        &bufferBarrierDesc);
}

void Command::ChangeRTVToPresent(ID3D12Resource* rtv, UINT backBufferNum)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(rtv);

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _commandList->ResourceBarrier(
        backBufferNum,
        &bufferBarrierDesc);
}

D3D12_RESOURCE_BARRIER Command::GetBufferBarrierDesc(
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

void Command::SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    _commandList->OMSetRenderTargets(1, &handle, true, nullptr);
}




HRESULT Command::CreateCommandAllocator(ID3D12Device* device)
{
    return device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(_commandAllocator.ReleaseAndGetAddressOf()));
}

HRESULT Command::CreateCommandList(ID3D12Device* device)
{
    return device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        _commandAllocator.Get(),
        nullptr,
        IID_PPV_ARGS(_commandList.ReleaseAndGetAddressOf()));
}

HRESULT Command::CreateCommandQueue(ID3D12Device* device)
{
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc =
        GetCommandQueueDesc();

    return device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(_commandQueue.ReleaseAndGetAddressOf()));
}




D3D12_COMMAND_QUEUE_DESC Command::GetCommandQueueDesc()
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

void Command::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
    float clearRTVColor[] =
        {1.0f, 1.0f, 0.0f, 1.0f};
    _commandList->ClearRenderTargetView(
        handle, clearRTVColor, 0, nullptr);
}

void Command::ExecuteCommand()
{
    ID3D12CommandList* commandLists[] = {_commandList.Get()};
    _commandQueue->ExecuteCommandLists(1, commandLists);
}

void Command::CommandClose()
{
    _commandList->Close();
}

void Command::CommandReset()
{
    _commandAllocator->Reset();
    _commandList->Reset(_commandAllocator.Get(), nullptr);
}