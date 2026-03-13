#include"MoveForward.h"

// é¿çs
void MoveForward::Exe()
{
    _piece->MoveY(0.01f);
}
// é¿çséÊÇËè¡Çµ
void MoveForward::Undo()
{

}




MoveForward::MoveForward(Piece* piece) : Move(piece){}
MoveForward::~MoveForward(){}