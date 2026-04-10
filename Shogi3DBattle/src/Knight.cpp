#include"Knight.h"

Knight::Knight()
{
    _gameObjType = GameObjType::KNIGHT;

    float mmBottomWidth  = 235.0f;
    float mmHeight       = 275.0f;
    _vertices = CreatePieceVertices(mmBottomWidth, mmHeight);
}