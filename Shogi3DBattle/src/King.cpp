#include"King.h"

King::King()
{
    _gameObjType = GameObjType::KING;

    float mmBottomWidth  = 285.0f;
    float mmHeight       = 320.0f;
    _vertices = CreatePieceVertices(mmBottomWidth, mmHeight);
}