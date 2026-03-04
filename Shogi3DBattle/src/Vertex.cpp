#include"Vertex.h"

#include<memory>
#include<cassert>

#include"VertexStruct.h"

// 頂点オブジェクト作成
HRESULT Vertex::CreateVertexObj(
    VertexArg::GetCreateVertexObjArg arg)
{
    // 頂点バッファ作成
    if (FAILED(CreateVertexBuff(
        arg.device, arg.heapProp, arg.resourceDesc, arg.vertexByte)))
    {
        assert(false); return E_FAIL;
    }
    // 頂点バッファにマップ
    if (FAILED(MapVertexToBuff(
        arg.vertexPtr)))
    {
        assert(false); return E_FAIL;
    }
    // インデックスバッファ作成
    if (FAILED(CreateIndexBuff(
        arg.device, arg.heapProp, arg.resourceDesc, arg.indexByte)))
    {
        assert(false); return E_FAIL;
    }
    // インデックスバッファにマップ
    if (FAILED(MapIndexToBuff(
        arg.indexPtr)))
    {
        assert(false); return E_FAIL;
    }
}

// 頂点バッファ作成
HRESULT Vertex::CreateVertexBuff(
    ID3D12Device* device,
    D3D12_HEAP_PROPERTIES heapProp,
    D3D12_RESOURCE_DESC   resourceDesc,
    unsigned int vertexByte)
{
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
HRESULT Vertex::MapVertexToBuff(
    std::vector<VertexStruct::Vertex> vertexPtr)
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
HRESULT Vertex::CreateIndexBuff(
    ID3D12Device* device,
    D3D12_HEAP_PROPERTIES heapProp,
    D3D12_RESOURCE_DESC   resourceDesc,
    unsigned int indexByte)
{
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
HRESULT Vertex::MapIndexToBuff(
    std::vector<unsigned short> indexPtr)
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