#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<memory>
#include<wrl.h>
#include<vector>
#include<array>

class Draw;

class DX12
{
template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
    HWND _hwnd;
    const int _bufferNum = 2;

    ComPtr<ID3D12Device>  _device;
    ComPtr<IDXGIFactory6> _dxgiFactory;

    ComPtr<ID3D12DescriptorHeap>        _rtvHeap;
    std::vector<ComPtr<ID3D12Resource>> _rtvs;

 
    HRESULT CreateFactory();
    HRESULT CreateDevice();
    
    HRESULT CreateRTVHeap();
    HRESULT CreateRTV();

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
    ComPtr<IDXGIAdapter>              _usingAdapter;

    void CreateUsedAdapterLists();
    void DecisionUsingAdapter();


    HRESULT SetBufferToRTV(UINT);


    D3D12_DESCRIPTOR_HEAP_DESC
        GetRTVHeapDesc();

    D3D12_CPU_DESCRIPTOR_HANDLE
        GetRTVHandle(UINT idx);

    
    
    // 描画オブジェクト
    std::shared_ptr<Draw> _draw; 

    HRESULT CreateDrawObject();

    UINT GetBackBufferIdx();

    void ChangeRTVToRenderTarget(ID3D12Resource* rtv);
    void ChangeRTVToPresent     (ID3D12Resource* rtv);

    void SetRenderTarget  (D3D12_CPU_DESCRIPTOR_HANDLE handle);
    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    void CloseCommand();
    void ExecuteCommand();
    void ResetCommand();

    void WaitProcessWithFence();

    void DisplaySwap();
    



public:
    DX12(HWND hwnd);

    bool CreateDX12Object();
    void ExecuteDX12();

    
    
};