#include"ShogiObj.h"

 void ShogiObj::SetVertices(std::vector<Vert> vertices){_vertices = vertices;}
 void ShogiObj::SetIndices(std::vector<unsigned short> indices){_indices = indices;}

// 頂点集合ポインタを返す
std::vector<ShogiObj::Vert> ShogiObj::GetVertices(){return _vertices;}
// 頂点１つ分のバイトサイズを返す
UINT ShogiObj::GetVertexByteSize(){return sizeof(_vertices[0]);}
// 頂点集合全体のバイトサイズを返す
UINT ShogiObj::GetVerticesByteSize(){return GetVertexByteSize() * static_cast<UINT>(_vertices.size());}

// 頂点インデックスポインタを返す
std::vector<unsigned short> ShogiObj::GetIndices(){return _indices;}
// 頂点インデックスの個数を返す
UINT ShogiObj::GetIdxNum(){return static_cast<UINT>(_indices.size());}
// 頂点インデックス１つ分のバイトサイズを返す
UINT ShogiObj::GetIndexByteSize(){return sizeof(_indices[0]);}
// 頂点インデックス全体のバイトサイズを返す
UINT ShogiObj::GetIndicesByteSize(){return GetIndexByteSize() * static_cast<UINT>(_indices.size());}
// 将棋オブジェクトIDセット
void ShogiObj::SetId(UINT id){_id = id;}
// 将棋オブジェクトIDを返す
UINT ShogiObj::GetId(){return _id;}
// テクスチャIDセット
void ShogiObj::SetTexId(UINT texId){_texId = texId;}
// テクスチャIDを返す
UINT ShogiObj::GetTexId(){return _texId;}


DirectX::XMMATRIX ShogiObj::GetWorldMat(){return _worldMat;} // ワールド行列を返す


void ShogiObj::SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address){_vertAddress = address;} // 頂点アドレスセット
D3D12_GPU_VIRTUAL_ADDRESS ShogiObj::GetVertAddress(){return _vertAddress;}                // 頂点アドレスを返す
void ShogiObj::SetIdxAddress (D3D12_GPU_VIRTUAL_ADDRESS address){_idxAddress  = address;} // インデックスアドレスセット
D3D12_GPU_VIRTUAL_ADDRESS ShogiObj::GetIdxAddress (){return _idxAddress;}                 // インデックスアドレスを返す

ShogiObj::ShogiObj(){}
ShogiObj::~ShogiObj(){}