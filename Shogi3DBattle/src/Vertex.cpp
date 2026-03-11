#include"Vertex.h"

// 頂点集合ポインタを返す
std::vector<VertexStruct::Vertex> Vertex::GetVerticesPtr()
{
    return _vertices;
}

// 頂点１つ分のバイトサイズを返す
unsigned int Vertex::GetVertexByteSize()
{
    return sizeof(_vertices[0]);
}

// 頂点集合全体のバイトサイズを返す
unsigned int Vertex::GetVerticesByteSize()
{
    return GetVertexByteSize() * _vertices.size();
}




// 頂点インデックスポインタを返す
std::vector<unsigned short> Vertex::GetIndicesPtr()
{
    return _indices;
}

unsigned int Vertex::GetIndicesNum()
{
    return _indices.size();
}

// 頂点インデックス１つ分のバイトサイズを返す
unsigned int Vertex::GetIndexByteSize()
{
    return sizeof(_indices[0]);
}

// 頂点インデックス全体のバイトサイズを返す
unsigned int Vertex::GetIndicesByteSize()
{
    return GetIndexByteSize() * _indices.size();
}

Vertex::Vertex(){}
Vertex::~Vertex(){}