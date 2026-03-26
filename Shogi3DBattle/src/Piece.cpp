#include"Piece.h"

// ワールド行列に平行移動を追加する
void Piece::Move(DirectX::XMFLOAT3 vec)
{
    _worldMat *= DirectX::XMMatrixTranslation(vec.x, vec.y, vec.z);
}

Piece::Piece(){}
Piece::~Piece(){}