#include"Board9x9.h"

unsigned int Board9x9::GetBoardSquareNum(){return 9;} // «Šû”Õ‚Ìƒ}ƒX”

Board9x9::Board9x9() : I_Board(100.0f)
{
    SetGameObjType(GameObjType::BOARD_99);
}