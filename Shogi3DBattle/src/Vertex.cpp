#include"Vertex.h"

#include<memory>
#include<cassert>

// 頂点オブジェクト作成
HRESULT Vertex::CreateVertexObj(
    VertexArg::GetCreateVertexObjArg arg)
{
    // 頂点バッファ作成
    if (FAILED(CreateVertexBuff(arg.device, arg.vertexByte)))
    {
        assert(false); return E_FAIL;
    }
    // 頂点バッファにマップ
    if (FAILED(MapVertexBuff(arg.vertexPtr)))
    {
        assert(false); return E_FAIL;
    }
    // インデックスバッファ作成
    if (FAILED(CreateIndexBuff(arg.device, arg.indicesByte)))
    {
        assert(false); return E_FAIL;
    }
    // インデックスバッファにマップ
    if (FAILED(MapIndexBuff(arg.indexPtr)))
    {
        assert(false); return E_FAIL;
    }
}

// 頂点バッファ作成
HRESULT Vertex::CreateVertexBuff(ID3D12Device* device, unsigned int vertexByte)
{
    D3D12_HEAP_PROPERTIES heapProp = GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetResourceDesc();

    resourceDesc.Width = vertexByte;

    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_vertexBuff.ReleaseAndGetAddressOf()));
}

// 頂点バッファにマップ
HRESULT Vertex::MapVertexBuff(std::vector<VertexStruct::Vertex> vertexPtr)
{
    std::shared_ptr<VertexStruct::Vertex> vertexMap;

    HRESULT result = _vertexBuff->Map(
        0, nullptr, (void**)&vertexMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto vertices = vertexPtr;

    std::copy(vertices.begin(), vertices.end(), vertexMap.get());

    _vertexBuff->Unmap(0, nullptr);

    return S_OK;
}

// インデックスバッファ作成
HRESULT Vertex::CreateIndexBuff(ID3D12Device* device, unsigned int indexByte)
{
    D3D12_HEAP_PROPERTIES heapProp = GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetResourceDesc();

    resourceDesc.Width = indexByte;

    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_indexBuff.ReleaseAndGetAddressOf()));

}

// インデックスバッファにマップ
HRESULT Vertex::MapIndexBuff(std::vector<unsigned short> indexPtr)
{
    std::shared_ptr<unsigned short> indexMap;

    HRESULT result = _indexBuff->Map(
        0, nullptr, (void**)&indexMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto indices = indexPtr;
    
    std::copy(indices.begin(), indices.end(), indexMap.get());

    _indexBuff->Unmap(0, nullptr);
    
    return S_OK;
}




// ヒーププロパティ
D3D12_HEAP_PROPERTIES Vertex::GetHeapProp()
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
D3D12_RESOURCE_DESC Vertex::GetResourceDesc()
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
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




// 頂点バッファを渡す
ID3D12Resource* Vertex::GetVertexBuff()
{
    return _vertexBuff.Get();
}

// インデックスバッファを渡す
ID3D12Resource* Vertex::GetIndexBuff()
{
    return _indexBuff.Get();
}




Vertex::Vertex(){}
Vertex::~Vertex(){}