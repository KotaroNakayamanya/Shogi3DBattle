#pragma once

#include<vector>
#include"VertexStruct.h"

class ShogiObj
{
protected:
    std::vector<VertexStruct::Vertex> _vertices; // 頂点集合
    std::vector<unsigned short>       _indices;  // 頂点インデックス

public:
    std::vector<VertexStruct::Vertex> GetVerticesPtr(); // 頂点集合を返す
    unsigned int GetVertexByteSize();   // 頂点１つ分のバイトサイズを返す
    unsigned int GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    std::vector<unsigned short> GetIndicesPtr(); // 頂点インデックスを返す
    unsigned int GetIdxNum();      // 頂点インデックスの個数を返す
    unsigned int GetIndexByteSize();   // 頂点インデックス1つ分のバイトサイズを返す
    unsigned int GetIndicesByteSize(); // 頂点インデックス全体のバイトサイズを返す

    ShogiObj();
    ~ShogiObj();
};