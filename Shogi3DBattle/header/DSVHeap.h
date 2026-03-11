#pragma once

#include<d3d12.h>
#include<wrl.h>

class DSVHeap
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12DescriptorHeap> _dsvHeap; // DSVヒープ

    D3D12_DESCRIPTOR_HEAP_DESC GetDSVHeapDesc(); // DSVヒープディスクリプタ

    void CreateDSV(ID3D12Device* device, ID3D12Resource* dsBuff); // DSV作成
    D3D12_DEPTH_STENCIL_VIEW_DESC GetDSVDesc(); // DSVディスクリプタ

public:
    HRESULT CreateDSVHeap( // ヒープ作成
        ID3D12Device* device, ID3D12Resource* dsBuff);

    D3D12_CPU_DESCRIPTOR_HANDLE GetDSVStartHandle(); // DSVハンドルを返す

    ID3D12DescriptorHeap* GetDSVHeap(); // DSVヒープを返す

    DSVHeap();
    ~DSVHeap();
};