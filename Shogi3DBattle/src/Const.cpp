#include"Const.h"

#include<DirectXMath.h>
#include<cassert>
#include<memory>

// コンスタントオブジェクト作成
HRESULT Const::CreateConstObj(ID3D12Device* device)
{
    // コンスタントバッファ作成
    if (FAILED(CreateBuff(device)))
    {
        assert(false); return E_FAIL;
    }
    // コンスタントバッファにマップ
    if (FAILED(MapBuff()))
    {
        assert(false); return E_FAIL;
    }
    // ディスクリプタヒープ作成
    if (FAILED(CreateHeap(device)))
    {
        assert(false); return E_FAIL;
    }
    // CBV作成
    CreateCBV(device);
}

// コンスタントバッファ作成
HRESULT Const::CreateBuff(ID3D12Device* device)
{
    D3D12_HEAP_PROPERTIES heapProp =
        GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc =
        GetResourceDesc();

    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_buff.ReleaseAndGetAddressOf()));
}

// コンスタントバッファにマップ
HRESULT Const::MapBuff()
{
    HRESULT result;

    std::shared_ptr<DirectX::XMMATRIX> map;

    result = _buff->Map(0, nullptr, (void**)&map);
    if (FAILED(result))
    {
        assert(false); return result;
    }

    DirectX::XMMATRIX mat = DirectX::XMMatrixIdentity();
    *map = mat;

    auto a = *map;

    _buff->Unmap(0, nullptr);

    return S_OK;
}

// ディスクリプタヒープ作成
HRESULT Const::CreateHeap(ID3D12Device* device)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc =
        GetHeapDesc();

    return device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_heap.ReleaseAndGetAddressOf()));
}

// CBV作成
void Const::CreateCBV(ID3D12Device* device)
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc =
        GetCBVDesc();

    device->CreateConstantBufferView(
        &cbvDesc,
        _heap->GetCPUDescriptorHandleForHeapStart());
}




// ヒーププロパティ
D3D12_HEAP_PROPERTIES Const::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

// リソースディスクリプタ
D3D12_RESOURCE_DESC Const::GetResourceDesc()
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Height =
        1;
    desc.Width =
        (1 + 0xff) & ~0xff;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count =
        1;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    return desc;
}

// テクスチャヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC Const::GetHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = // CBV用
        D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        1;
    desc.Flags = // シェーダから使用可能
        D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    return desc;
}

// CBVディスクリプタ
D3D12_CONSTANT_BUFFER_VIEW_DESC Const::GetCBVDesc()
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};

    desc.BufferLocation = _buff->GetGPUVirtualAddress();
    desc.SizeInBytes = _buff->GetDesc().Width * _buff->GetDesc().Height;

    return desc;
}




Const::Const(){}
Const::~Const(){}