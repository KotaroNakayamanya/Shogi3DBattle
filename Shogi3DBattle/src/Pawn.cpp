#include"Pawn.h"

Pawn::Pawn()
{
    _gameObjType = GameObjType::PAWN;

    float mmBottomWidth  = 215.0f;
    float mmHeight       = 260.0f;
    _vertices = CreatePieceVertices(mmBottomWidth, mmHeight);
}