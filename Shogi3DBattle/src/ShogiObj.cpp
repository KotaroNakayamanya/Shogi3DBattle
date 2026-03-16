#include"ShogiObj.h"

// 頂点集合ポインタを返す
std::vector<VertexStruct::Vertex> ShogiObj::GetVertices(){return _vertices;}
// 頂点１つ分のバイトサイズを返す
unsigned int ShogiObj::GetVertexByteSize(){return sizeof(_vertices[0]);}
// 頂点集合全体のバイトサイズを返す
unsigned int ShogiObj::GetVerticesByteSize(){return GetVertexByteSize() * _vertices.size();}

// 頂点インデックスポインタを返す
std::vector<unsigned short> ShogiObj::GetIndices(){return _indices;}
// 頂点インデックスの個数を返す
unsigned int ShogiObj::GetIdxNum(){return _indices.size();}
// 頂点インデックス１つ分のバイトサイズを返す
unsigned int ShogiObj::GetIndexByteSize(){return sizeof(_indices[0]);}
// 頂点インデックス全体のバイトサイズを返す
unsigned int ShogiObj::GetIndicesByteSize(){return GetIndexByteSize() * _indices.size();}


DirectX::XMMATRIX ShogiObj::GetWorldMat(){return _worldMat;} // ワールド行列を返す


void ShogiObj::SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address){_vertAddress = address;} // 頂点アドレスセット
D3D12_GPU_VIRTUAL_ADDRESS ShogiObj::GetVertAddress(){return _vertAddress;}                // 頂点アドレスを返す
void ShogiObj::SetIdxAddress (D3D12_GPU_VIRTUAL_ADDRESS address){_idxAddress  = address;} // インデックスアドレスセット
D3D12_GPU_VIRTUAL_ADDRESS ShogiObj::GetIdxAddress (){return _idxAddress;}                 // インデックスアドレスを返す

ShogiObj::ShogiObj(){}
ShogiObj::~ShogiObj(){}