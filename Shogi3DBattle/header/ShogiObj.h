#pragma once

#include<d3d12.h>
#include<vector>
#include"VertexStruct.h"

class ShogiObj
{
protected:
    std::vector<VertexStruct::Vertex> _vertices; // 頂点集合
    std::vector<unsigned short>       _indices;  // 頂点インデックス
    DirectX::XMMATRIX                 _worldMat; // ワールド行列
    D3D12_GPU_VIRTUAL_ADDRESS         _vertAddress; // 頂点アドレス
    D3D12_GPU_VIRTUAL_ADDRESS         _idxAddress;  // インデックスアドレス

public:
    std::vector<VertexStruct::Vertex> GetVertices(); // 頂点集合を返す
    unsigned int GetVertexByteSize();   // 頂点１つ分のバイトサイズを返す
    unsigned int GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    std::vector<unsigned short> GetIndices(); // 頂点インデックスを返す
    unsigned int GetIdxNum();      // 頂点インデックスの個数を返す
    unsigned int GetIndexByteSize();   // 頂点インデックス1つ分のバイトサイズを返す
    unsigned int GetIndicesByteSize(); // 頂点インデックス全体のバイトサイズを返す

    void SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address); // 頂点アドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetVertAddress();             // 頂点アドレスを返す
    void SetIdxAddress (D3D12_GPU_VIRTUAL_ADDRESS address); // インデックスアドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetIdxAddress();              // インデックスアドレスを返す

    DirectX::XMMATRIX GetWorldMat(); // ワールド行列を返す

    ShogiObj();
    ~ShogiObj();
};