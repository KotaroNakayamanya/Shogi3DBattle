#include"Rook.h"

Rook::Rook()
{
    _gameObjType = GameObjType::ROOK;

    float mmBottomWidth  = 260.0f;
    float mmHeight       = 300.0f;
    SetPieceVertices(mmBottomWidth, mmHeight);
}