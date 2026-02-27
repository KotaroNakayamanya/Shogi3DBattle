#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<memory>
#include<wrl.h>
#include<vector>
#include<array>

class Command;

class DX12
{
template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
    HWND _hwnd;
    const int _bufferNum = 2;

    ComPtr<ID3D12Device>    _device;
    ComPtr<IDXGIFactory6>   _dxgiFactory;
    ComPtr<IDXGISwapChain4> _swapChain;
    ComPtr<ID3D12Fence> _fence;

    UINT64 _fenceVal = 0;

    ComPtr<ID3D12DescriptorHeap> _rtvHeap;
    std::vector<ComPtr<ID3D12Resource>> _rtvs;

 
    HRESULT CreateFactory();
    HRESULT CreateDevice();
    HRESULT CreateSwapChain();
    HRESULT CreateRTVHeap();
    HRESULT CreateRTV();
    HRESULT SetBufferToRTV(int i);
    HRESULT CreateFence();

    
    DXGI_SWAP_CHAIN_DESC1
        GetSwapChainDesc();
    D3D12_DESCRIPTOR_HEAP_DESC
        GetRTVHeapDesc();

    D3D12_CPU_DESCRIPTOR_HANDLE
        GetRTVHandle(UINT idx);

    void WaitProcessWithFence();
    void CommandReset();
        

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
    

    

    

    // コマンドオブジェクト
    std::shared_ptr<Command> _command;
    ID3D12CommandQueue* GetCommandQueue();
    HRESULT CreateCommandObject();
    void SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);
    void ChangeRTVToRenderTarget(UINT idx);
    void ChangeRTVToPresent(UINT idx);

    void CommandClose();
    void ExecuteCommand();
    void ClearRenderTarget(
        D3D12_CPU_DESCRIPTOR_HANDLE handle);

public:
    DX12();
    DX12(HWND hwnd);

    bool CreateDX12BasicObject();
    void RunDX12();

    
    
};