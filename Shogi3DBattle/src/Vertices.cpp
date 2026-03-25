#include"Vertices.h"

// 頂点１つ分のバイトサイズを返す
UINT Vertices::GetVertByteSize()
{
    return sizeof(_vertices[0]);
}

// 頂点集合全体のバイトサイズを返す
UINT Vertices::GetVerticesByteSize()
{
    auto aaa = GetVertByteSize();
    auto bbb = static_cast<UINT>(_vertices.size());
    return GetVertByteSize() * static_cast<UINT>(_vertices.size());
}

void Vertices::SetVertices(std::vector<Vertices::Vert> vertices){_vertices = vertices;} // 頂点集合セット
std::vector<Vertices::Vert> Vertices::GetVertices()             {return _vertices;}     // 頂点集合を返す

Vertices::Vertices(){}
Vertices::~Vertices(){}