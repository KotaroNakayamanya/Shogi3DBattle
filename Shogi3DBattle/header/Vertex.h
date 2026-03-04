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


    HRESULT CreateVertexBuff(ID3D12Device* device, unsigned int vertexByte); // 頂点バッファ作成
    HRESULT CreateIndexBuff(ID3D12Device* device, unsigned int indexByte); // インデックスバッファ作成

    HRESULT MapVertexBuff(std::vector<VertexStruct::Vertex> vertexPtr); // 頂点をバッファにマップ
    HRESULT MapIndexBuff(std::vector<unsigned short> indexPtr);  // インデックスをバッファにマップ

    D3D12_HEAP_PROPERTIES GetHeapProp(); // 頂点ヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc();  // リソースディスクリプタ

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