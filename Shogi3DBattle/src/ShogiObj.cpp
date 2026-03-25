#include"ShogiObj.h"

// 頂点１つ分のバイトサイズを返す
UINT ShogiObj::GetVertexByteSize(){return sizeof(_vertices[0]);}
// 頂点集合全体のバイトサイズを返す
UINT ShogiObj::GetVerticesByteSize(){return GetVertexByteSize() * static_cast<UINT>(_vertices.size());}


// ワールド行列セット
void ShogiObj::SetWorldMat( DirectX::XMMATRIX mat){_worldMat = mat;}
// ワールド行列を返す
DirectX::XMMATRIX ShogiObj::GetWorldMat(){return _worldMat;}

// 頂点集合セット
void ShogiObj::SetVertices(std::vector<Vert> vertices){_vertices = vertices;}
// 頂点集合を返す
std::vector<ShogiObj::Vert> ShogiObj::GetVertices(){return _vertices;}
// 将棋オブジェクトIDセット
void  ShogiObj::SetObjId(UCHAR objId){_objId = objId;}
// 将棋オブジェクトIDを返す
UCHAR ShogiObj::GetObjId(){return _objId;}
// テクスチャIDセット
void  ShogiObj::SetTexId(UCHAR texId){_texId = texId;}
// テクスチャIDを返す
UCHAR ShogiObj::GetTexId(){return _texId;}
// 頂点アドレスセット
void ShogiObj::SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address){_vertAddress = address;}
// 頂点アドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS ShogiObj::GetVertAddress(){return _vertAddress;}

ShogiObj::ShogiObj(){}
ShogiObj::~ShogiObj(){}