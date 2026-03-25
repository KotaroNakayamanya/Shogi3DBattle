#include"Piece.h"

// x軸方向に動くようにワールド行列を変換する
void Piece::MoveX(float x)
{
    //_worldMat *= DirectX::XMMatrixTranslation(x, 0, 0);
    auto moveXMat = DirectX::XMMatrixTranslation(x, 0, 0);
    auto newMat = _worldMat->GetMat() * moveXMat;

    _worldMat->SetWorldMat(newMat);
}

// y軸方向に動くようにワールド行列を変換する
void Piece::MoveY(float y)
{
    auto moveYMat = DirectX::XMMatrixTranslation(0, y, 0);
    auto newMat = _worldMat->GetMat() * moveYMat;

    _worldMat->SetWorldMat(newMat);
}

Piece::Piece(){}
Piece::~Piece(){}