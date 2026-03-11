#include"MoveLeft.h"

// é¿çs
void MoveLeft::Exe()
{
    _piece->MoveX(-0.1f);
}
// é¿çséÊÇËè¡Çµ
void MoveLeft::Undo()
{

}




MoveLeft::MoveLeft(Piece* piece) : Move(piece){}
MoveLeft::~MoveLeft(){}