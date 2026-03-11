#include"VertBuff.h"
#include<memory>
#include<cassert>

// 頂点オブジェクト作成
HRESULT VertBuff::CreateVertBuff(ID3D12Device* device, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetResourceDesc(byteSize);

    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_vertBuff.ReleaseAndGetAddressOf()));
}

// 頂点バッファに書き込み
HRESULT VertBuff::WriteVertBuff(std::vector<VertexStruct::Vertex> vertexPtr)
{
    std::shared_ptr<VertexStruct::Vertex> vertexMap;

    HRESULT result = _vertBuff->Map(
        0, nullptr, (void**)&vertexMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto vertices = vertexPtr;

    std::copy(vertices.begin(), vertices.end(), vertexMap.get());

    _vertBuff->Unmap(0, nullptr);

    return S_OK;
}
// ヒーププロパティ
D3D12_HEAP_PROPERTIES VertBuff::GetHeapProp()
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
D3D12_RESOURCE_DESC VertBuff::GetResourceDesc(UINT byteSize)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width =
        byteSize;
    desc.Height =
        1;
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




// 頂点バッファを返す
ID3D12Resource* VertBuff::GetVertBuff()
{
    return _vertBuff.Get();
}




VertBuff::VertBuff(){}
VertBuff::~VertBuff(){}