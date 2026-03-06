#pragma once

#include<d3d12.h>
#include<wrl.h>

#include"CSUHeapArg.h"

class CSUHeap
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12DescriptorHeap> _heap; // CBV,SRV,UAVヒープ

    HRESULT CreateHeap(ID3D12Device* device); // ヒープ作成
    void CreateCBV(ID3D12Device* device, ID3D12Resource* cbvBuff); // CBV作成
    void CreateSRV(ID3D12Device* device, ID3D12Resource* srvBuff); // SRV作成
    
    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(); // ヒープディスクリプタ
    D3D12_CONSTANT_BUFFER_VIEW_DESC GetCBVDesc(ID3D12Resource* cbvBuff); // CBVディスクリプタ
    D3D12_SHADER_RESOURCE_VIEW_DESC GetSRVDesc(); // SRVディスクリプタ
   
public:
    HRESULT CreateHeap(CSUHeapArg::CreateCSUHeapArg arg); // ヒープ作成
    ID3D12DescriptorHeap* GetHeap(); // ヒープを渡す

    CSUHeap();
    ~CSUHeap();
};