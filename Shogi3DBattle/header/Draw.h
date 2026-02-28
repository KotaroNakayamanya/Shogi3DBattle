#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

class Draw
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    UINT _bufferNum;
    UINT _fenceVal = 0;
    
    ComPtr<ID3D12CommandAllocator>    _commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> _commandList;
    ComPtr<ID3D12CommandQueue>        _commandQueue;
    ComPtr<IDXGISwapChain4>           _swapChain;
    ComPtr<ID3D12Fence>               _fence;

    D3D12_RESOURCE_BARRIER GetBufferBarrierDesc(ID3D12Resource* rtv);


public:
    Draw(UINT bufferNum);

    ID3D12CommandAllocator**    GetCommandAllocatorPtr();
    ID3D12GraphicsCommandList** GetCommandListPtr();
    ID3D12CommandQueue**        GetCommandQueuePtr();
    IDXGISwapChain4**           GetSwapChainPtr();
    ID3D12Fence**               GetFencePtr();
    UINT                        GetFenceVal();

    HRESULT SetBufferToRTV(UINT i, ID3D12Resource** rtvPtr);

    UINT GetBackBufferIdx();

    void SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    // RTVのレンダーターゲット⇔Presentの切り替え
    void ChangeRTVBarrierToRenderTarget(ID3D12Resource* rtv);
    void ChangeRTVBarrierToPresent     (ID3D12Resource* rtv);

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    void CloseCommand  ();
    void ExecuteCommand();
    void ResetCommand  ();

    void WaitProcessWithFence();

    void DisplaySwap();

    
};