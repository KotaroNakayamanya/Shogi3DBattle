#include"Board9x9.h"

Board9x9::Board9x9()
{
    _gameObjType = GameObjType::BOARD_99;

    float size = 100.0f;
    _vertices = CreateBoardVertices(size);
}