#include"Lance.h"

Lance::Lance()
{
    _gameObjType = GameObjType::LANCE;

    float mmBottomWidth  = 225.0f;
    float mmHeight       = 280.0f;
    SetPieceVertices(mmBottomWidth, mmHeight);
}