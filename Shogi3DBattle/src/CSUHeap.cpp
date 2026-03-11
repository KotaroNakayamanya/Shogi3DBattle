#include"CSUHeap.h"
#include<cassert>

// ヒープ作成
HRESULT CSUHeap::CreateHeap(HeapArg::CreateCSUHeapArg arg)
{
    HRESULT result;

    // ヒープ作成
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetCSUHeapDesc();

    result = arg.device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_csuHeap.ReleaseAndGetAddressOf()));
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    // ビュー作成
    CreateCBV(arg.device, arg.buff1);
    CreateSRV(arg.device, arg.buff2);
    

    return S_OK;
}

// CBV作成
void CSUHeap::CreateCBV(ID3D12Device* device, ID3D12Resource* cbvBuff)
{
    auto csuHandle = _csuHeap->GetCPUDescriptorHandleForHeapStart();

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = GetCBVDesc(cbvBuff);

    device->CreateConstantBufferView(
        &cbvDesc,
        csuHandle);
}

// SRV作成
void CSUHeap::CreateSRV(ID3D12Device* device, ID3D12Resource* srvBuff)
{
    
    auto handle = _csuHeap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += device->GetDescriptorHandleIncrementSize(
                    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = GetSRVDesc();

    device->CreateShaderResourceView(
        srvBuff,
        &srvDesc,
        handle);
}




// ヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC CSUHeap::GetCSUHeapDesc()
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
D3D12_SHADER_RESOURCE_VIEW_DESC CSUHeap::GetSRVDesc()
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
D3D12_CONSTANT_BUFFER_VIEW_DESC CSUHeap::GetCBVDesc(ID3D12Resource* cbvBuff) 
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};

    desc.BufferLocation = cbvBuff->GetGPUVirtualAddress();
    desc.SizeInBytes = cbvBuff->GetDesc().Width * cbvBuff->GetDesc().Height;

    return desc;
}

// ヒープを渡す
ID3D12DescriptorHeap* CSUHeap::GetHeap()
{
    return _csuHeap.Get();
}




CSUHeap::CSUHeap(){}
CSUHeap::~CSUHeap(){}