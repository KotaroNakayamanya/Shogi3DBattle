#include"B_Piece.h"

// 移動
void B_Piece::Move(DirectX::XMFLOAT3 vec)
{
    auto worldMat = _worldMat->GetMat();
    worldMat *= DirectX::XMMatrixTranslation(vec.x, vec.y, vec.z);
    _worldMat->SetWorldMat(worldMat);
}

Vertices* B_Piece::GetVertices(){return _vertices.get();} // 頂点集合を返す

void      B_Piece::SetWorldMat(WorldMat* mat){_worldMat.reset(mat);}   // ワールド行列セット
WorldMat* B_Piece::GetWorldMat()             {return _worldMat.get();} // ワールド行列を返す