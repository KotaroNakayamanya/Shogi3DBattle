#include"MoveRight.h"

// é¿çs
void MoveRight::Exe()
{
    _piece->MoveX(0.01f);
}
// é¿çséÊÇËè¡Çµ
void MoveRight::Undo()
{

}




MoveRight::MoveRight(Piece* piece) : Move(piece){}
MoveRight::~MoveRight(){}