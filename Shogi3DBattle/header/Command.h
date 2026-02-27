#pragma once

#include<d3d12.h>
#include<wrl.h>

class Command
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandAllocator>    _commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> _commandList;
    ComPtr<ID3D12CommandQueue>        _commandQueue;

    HRESULT CreateCommandAllocator(ID3D12Device* device);
    HRESULT CreateCommandList     (ID3D12Device* device);
    HRESULT CreateCommandQueue    (ID3D12Device* device);

    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc();

    D3D12_RESOURCE_BARRIER GetBufferBarrierDesc(
        ID3D12Resource* rtv);


public:
    ID3D12CommandQueue* GetCommandQueue();
    HRESULT CreateCommandObject(ID3D12Device* device);
    void SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);
    void ChangeRTVToRenderTarget(ID3D12Resource* rtv, UINT backBufferNum);
    void ChangeRTVToPresent(ID3D12Resource* rtv, UINT backBufferNum);
    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    void CommandClose();
    void ExecuteCommand();
    void CommandReset();
    
};