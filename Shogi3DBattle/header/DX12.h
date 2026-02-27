#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>
#include<array>

class DX12Basic;

class DX12
{
private:
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    HWND _hwnd;
    const int _bufferNum = 2;

    // DXGI
    ComPtr<IDXGIFactory6>   _dxgiFactory;
    ComPtr<IDXGISwapChain4> _swapChain;

    // Direct3D
    ComPtr<ID3D12Device>              _device;
    ComPtr<ID3D12CommandAllocator>    _commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> _commandList;
    ComPtr<ID3D12CommandQueue>        _commandQueue;

    ComPtr<ID3D12Fence> _fence;
    UINT64 _fenceVal = 0;

    ComPtr<ID3D12DescriptorHeap> _rtvHeap;
    std::vector<ComPtr<ID3D12Resource>> _rtvs;

    

    HRESULT CreateFactory();
    HRESULT CreateDevice();
    HRESULT CreateCommandAllocator();
    HRESULT CreateCommandList();
    HRESULT CreateCommandQueue();
    HRESULT CreateSwapChain();
    HRESULT CreateRTVHeap();
    HRESULT CreateRTV();
    HRESULT SetBufferToRTV(int i);
    HRESULT CreateFence();

    D3D12_COMMAND_QUEUE_DESC
        GetCommandQueueDesc();
    DXGI_SWAP_CHAIN_DESC1
        GetSwapChainDesc();
    D3D12_DESCRIPTOR_HEAP_DESC
        GetRTVHeapDesc();

    D3D12_CPU_DESCRIPTOR_HANDLE
        GetRTVHandle(UINT idx);

    void SetRTVToRenderTargetWithBarrier(
        UINT idx);
    void SetRTVToPresentWithBarrier(
        UINT idx);
    void WaitProcessWithFence();
    void CommandReset();

    D3D12_RESOURCE_BARRIER GetBufferBarrierDesc(
        ID3D12Resource* rtv);
        

    // GPU機能レベル一覧
    std::array<D3D_FEATURE_LEVEL, 5> _featureLevels =
    {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };
    std::vector<ComPtr<IDXGIAdapter>> _adapters;
    ComPtr<IDXGIAdapter> _usingAdapter;
    void CreateUsedAdapterLists();
    void DecisionUsingAdapter();
    void ExecuteCommand();

    
    


public:
    DX12();
    DX12(HWND hwnd);
    bool CreateDX12BasicObject();
    void RunDX12();
};