#include"Gold.h"

Gold::Gold()
{
    _gameObjType = GameObjType::GOLD;

    float mmBottomWidth  = 250.0f;
    float mmHeight       = 285.0f;
    _vertices = CreatePieceVertices(mmBottomWidth, mmHeight);
}