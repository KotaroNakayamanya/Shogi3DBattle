#include"Piece.h"

// x軸方向に動くようにワールド行列を変換する
void Piece::MoveX(float x)
{
    _worldMat *= DirectX::XMMatrixTranslation(x, 0, 0);
}

// y軸方向に動くようにワールド行列を変換する
void Piece::MoveY(float y)
{
    _worldMat *= DirectX::XMMatrixTranslation(0, y, 0);
}

Piece::Piece(){}
Piece::~Piece(){}