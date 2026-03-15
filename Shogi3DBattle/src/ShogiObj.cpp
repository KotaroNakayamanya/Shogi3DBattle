#include"ShogiObj.h"

// 頂点集合ポインタを返す
std::vector<VertexStruct::Vertex> ShogiObj::GetVerticesPtr(){return _vertices;}
// 頂点１つ分のバイトサイズを返す
unsigned int ShogiObj::GetVertexByteSize(){return sizeof(_vertices[0]);}
// 頂点集合全体のバイトサイズを返す
unsigned int ShogiObj::GetVerticesByteSize(){return GetVertexByteSize() * _vertices.size();}

// 頂点インデックスポインタを返す
std::vector<unsigned short> ShogiObj::GetIndicesPtr(){return _indices;}
// 頂点インデックスの個数を返す
unsigned int ShogiObj::GetIdxNum(){return _indices.size();}
// 頂点インデックス１つ分のバイトサイズを返す
unsigned int ShogiObj::GetIndexByteSize(){return sizeof(_indices[0]);}
// 頂点インデックス全体のバイトサイズを返す
unsigned int ShogiObj::GetIndicesByteSize(){return GetIndexByteSize() * _indices.size();}

ShogiObj::ShogiObj(){}
ShogiObj::~ShogiObj(){}