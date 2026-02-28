#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<memory>
#include<wrl.h>
#include<vector>
#include<array>

class Draw;
class Buffer;
class Vertex;

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
    
    HRESULT CreateCommandAllocator();
    HRESULT CreateCommandList();
    HRESULT CreateCommandQueue();
    HRESULT CreateSwapChain();
    HRESULT CreateFence();
    HRESULT CreateRTVHeap();
    HRESULT CreateRTV();
    HRESULT CreateVertexBuffer();

    HRESULT SetBufferToRTV(UINT);
    D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc();

    DXGI_SWAP_CHAIN_DESC1    GetSwapChainDesc();
    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc();


    D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle(UINT idx);

    D3D12_HEAP_PROPERTIES GetHeapProperty();
    D3D12_RESOURCE_DESC GetResourceDesc();

    HRESULT MapVertexToBuffer();


    // バッファオブジェクト
    ComPtr<ID3D12Resource> _vertexBuffer;

    // 頂点オブジェクト
    std::vector<std::shared_ptr<Vertex>> _vertices;
    HRESULT CreateVertexSets();
    
    // 描画オブジェクト
    std::shared_ptr<Draw> _draw; 

    HRESULT CreateDrawObject();

    UINT GetBackBufferIdx();

    void ChangeRTVBarrierToRenderTarget(ID3D12Resource* rtv);
    void ChangeRTVBarrierToPresent     (ID3D12Resource* rtv);

    void SetRenderTarget  (D3D12_CPU_DESCRIPTOR_HANDLE handle);
    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    void SetVertexBuffer();
    
    D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();

    void ExecuteDraw();

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