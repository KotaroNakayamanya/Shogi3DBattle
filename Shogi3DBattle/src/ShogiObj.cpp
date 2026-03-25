#include"ShogiObj.h"

// 頂点１つ分のバイトサイズを返す
UINT ShogiObj::GetVertexByteSize(){return sizeof(_vertices[0]);}
// 頂点集合全体のバイトサイズを返す
UINT ShogiObj::GetVerticesByteSize(){return GetVertexByteSize() * static_cast<UINT>(_vertices.size());}




void ShogiObj::SetWorldMat( DirectX::XMMATRIX worldMat){_worldMat->SetWorldMat(worldMat);} // ワールド行列セット
DirectX::XMMATRIX ShogiObj::GetWorldMat(){return _worldMat->GetMat();}                     // ワールド行列を返す
void ShogiObj::SetVertices(std::vector<Vertices::Vert> vertices){_vertices = vertices;} // 頂点集合セット
std::vector<Vertices::Vert> ShogiObj::GetVertices(){return _vertices;} // 頂点集合を返す
void  ShogiObj::SetObjId(UCHAR objId){_objId = objId;} // 将棋オブジェクトIDセット
UCHAR ShogiObj::GetObjId(){return _objId;} // 将棋オブジェクトIDを返す
void  ShogiObj::SetTexId(UCHAR texId){_texId = texId;} // テクスチャIDセット
UCHAR ShogiObj::GetTexId(){return _texId;} // テクスチャIDを返す
void ShogiObj::SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address){_vertAddress = address;} // 頂点アドレスセット
D3D12_GPU_VIRTUAL_ADDRESS ShogiObj::GetVertAddress(){return _vertAddress;} // 頂点アドレスを返す

ShogiObj::ShogiObj()
{
    _worldMat = std::make_unique<WorldMat>();
}
ShogiObj::~ShogiObj(){}