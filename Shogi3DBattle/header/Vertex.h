#pragma once

#include<d3d12.h>
#include<wrl.h>

#include"VertexArg.h"

class Vertex
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
    ComPtr<ID3D12Resource> _vertexBuff; // 頂点バッファ
    ComPtr<ID3D12Resource> _indexBuff;  // インデックスバッファ


    HRESULT CreateVertexBuff( // 頂点バッファ作成
        ID3D12Device* device,
        D3D12_HEAP_PROPERTIES heapProperty,
        D3D12_RESOURCE_DESC   resourceDesc,
        unsigned int vertexByte);

    HRESULT CreateIndexBuff( // インデックスバッファ作成
        ID3D12Device* device,
        D3D12_HEAP_PROPERTIES heapProperty,
        D3D12_RESOURCE_DESC   resourceDesc,
        unsigned int indexByte);

    HRESULT MapVertexToBuff(std::vector<VertexStruct::Vertex> vertexPtr); // 頂点をバッファにマップ
    HRESULT MapIndexToBuff(std::vector<unsigned short> indexPtr);  // インデックスをバッファにマップ


public:
    // 頂点オブジェクト作成
    HRESULT CreateVertexObj(VertexArg::GetCreateVertexObjArg arg);
    // 頂点バッファを渡す
    ID3D12Resource* GetVertexBuff();
    // インデックスバッファを渡す
    ID3D12Resource* GetIndexBuff();

    Vertex();
    ~Vertex();
};