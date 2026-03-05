#include"Heap.h"

#include<cassert>

// ヒープオブジェクト作成
HRESULT Heap::CreateHeapObj(HeapArg::CreateHeapArg arg)
{
    // ヒープ作成
    if (FAILED(CreateHeap(arg.device)))
    {
        assert(false); return E_FAIL;
    }

    // ビュー作成
    CreateSRV(arg.device, arg.srvBuff);
    CreateCBV(arg.device, arg.cbvBuff);

    return S_OK;
}

// ヒープ作成
HRESULT Heap::CreateHeap(ID3D12Device* device)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetHeapDesc();

    return device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_heap.ReleaseAndGetAddressOf()));
}

// SRV作成
void Heap::CreateSRV(ID3D12Device* device, ID3D12Resource* srvBuff)
{
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = GetSRVDesc();

    auto handle = _heap->GetCPUDescriptorHandleForHeapStart();

    device->CreateShaderResourceView(
        srvBuff,
        &srvDesc,
        handle);
}

// CBV作成
void Heap::CreateCBV(ID3D12Device* device, ID3D12Resource* cbvBuff)
{
    auto handle = _heap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += device->GetDescriptorHandleIncrementSize(
                    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = GetCBVDesc(cbvBuff);

    device->CreateConstantBufferView(
        &cbvDesc,
        handle);
}




// ヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC Heap::GetHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};

    desc.Type = // SRV, CBV用
        D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        2;
    desc.Flags = // シェーダから使用可能
        D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    return desc;
}

// SRVディスクリプタ
D3D12_SHADER_RESOURCE_VIEW_DESC Heap::GetSRVDesc()
{
    D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Shader4ComponentMapping =
        D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    desc.ViewDimension =
        D3D12_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels =
        1;

    return desc;
}

// CBVディスクリプタ
D3D12_CONSTANT_BUFFER_VIEW_DESC Heap::GetCBVDesc(ID3D12Resource* cbvBuff) 
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};

    desc.BufferLocation = cbvBuff->GetGPUVirtualAddress();
    desc.SizeInBytes = cbvBuff->GetDesc().Width * cbvBuff->GetDesc().Height;

    return desc;
}

// ヒープを渡す
ID3D12DescriptorHeap* Heap::GetHeap()
{
    return _heap.Get();
}




Heap::Heap(){}
Heap::~Heap(){}