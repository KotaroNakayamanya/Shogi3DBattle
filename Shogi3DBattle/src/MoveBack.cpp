#include"MoveBack.h"

// é¿çs
void MoveBack::Exe()
{
    _piece->MoveY(-0.01f);
}
// é¿çséÊÇËè¡Çµ
void MoveBack::Undo()
{

}




MoveBack::MoveBack(Piece* piece) : Move(piece){}
MoveBack::~MoveBack(){}