#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>
#include"HeapArg.h"

class RTVHeap
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12DescriptorHeap> _heap; // RTVヒープ
    std::vector<ComPtr<ID3D12Resource>> _rtvs; // RTV

    HRESULT CreateRTV( // RTV作成
        ID3D12Device* device,
        IDXGISwapChain4* swapChain,
        UINT buffNum);

    HRESULT SetRTVBuffer( // RTVをバッファに対応
        IDXGISwapChain4* swapChain,
        UINT i);

    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(UINT buffNum); // ヒープディスクリプタ

public:
    HRESULT CreateHeap( // ヒープ作成
        ID3D12Device* device,
        IDXGISwapChain4* swapChain,
        UINT buffNum);

    ID3D12DescriptorHeap* GetHeap(); // ヒープを返す
    ID3D12Resource* GetRTV(UINT i); // RTVを返す

    RTVHeap();
    ~RTVHeap();
};