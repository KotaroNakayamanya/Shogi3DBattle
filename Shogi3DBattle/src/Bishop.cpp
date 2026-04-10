#include"Bishop.h"

Bishop::Bishop()
{
    _gameObjType = GameObjType::BISHOP;

    float mmBottomWidth  = 260.0f;
    float mmHeight       = 300.0f;
    SetPieceVertices(mmBottomWidth, mmHeight);
}