#include"Piece.h"

// ワールド行列に平行移動を追加する
void Piece::Move(DirectX::XMFLOAT3 vec)
{
    auto worldMat = _worldMat->GetMat();
    worldMat *= DirectX::XMMatrixTranslation(vec.x, vec.y, vec.z);
    _worldMat->SetWorldMat(worldMat);
}

Piece::Piece(){}
Piece::~Piece(){}