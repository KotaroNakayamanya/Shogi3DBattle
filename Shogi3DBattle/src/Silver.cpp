#include"Silver.h"

Silver::Silver()
{
    _gameObjType = GameObjType::SILVER;

    float mmBottomWidth  = 250.0f;
    float mmHeight       = 285.0f;
    SetPieceVertices(mmBottomWidth, mmHeight);
}