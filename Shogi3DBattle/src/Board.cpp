#include"Board.h"

// «Šû”Õ‚ğ5~5‚É•ÏX
void Board::ChangeBoardTo55()
{
    if(_texId == ShogiObj::BOARD_55) return;

    float rate = 6.0f / 10.0f;
    _worldMat = DirectX::XMMatrixScaling(rate, rate, rate);
}

// «Šû”Õ‚ğ9~9‚É•ÏX
void Board::ChangeBoardTo99()
{
    if(_texId == ShogiObj::BOARD_99) return;

    _worldMat = DirectX::XMMatrixIdentity();
}