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

    HRESULT CreateCommandAllocator(ID3D12Device*  device);
    HRESULT CreateCommandList     (ID3D12Device*  device);
    HRESULT CreateCommandQueue    (ID3D12Device*  device);
    HRESULT CreateSwapChain       (IDXGIFactory6* dxgiFactory, HWND hwnd);
    HRESULT CreateFence           (ID3D12Device*  device);

    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc();
    DXGI_SWAP_CHAIN_DESC1    GetSwapChainDesc();
    D3D12_RESOURCE_BARRIER GetBufferBarrierDesc(ID3D12Resource* rtv);


public:
    Draw(UINT bufferNum);

    UINT GetBackBufferIdx();
    //ID3D12CommandQueue* GetCommandQueue(); // スワップチェーン作成用

    HRESULT CreateDrawObject(ID3D12Device* device, IDXGIFactory6* dxgiFactory, HWND hwnd);
    void SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    // RTVのレンダーターゲット⇔Presentの切り替え
    void ChangeRTVToRenderTarget(ID3D12Resource* rtv);
    void ChangeRTVToPresent     (ID3D12Resource* rtv);

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    void CloseCommand  ();
    void ExecuteCommand();
    void ResetCommand  ();

    void WaitProcessWithFence();

    void DisplaySwap();

    HRESULT SetBufferToRTV(UINT i, ID3D12Resource** rtvPtr);
    
};