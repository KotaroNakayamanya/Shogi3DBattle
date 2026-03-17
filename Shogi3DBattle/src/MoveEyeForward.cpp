#include"MoveEyeForward.h"

// é¿çs
void MoveEyeForward::Exe()
{
    //_viewMat->MoveEyeForward(0.1f);
}

// é¿çséÊÇËè¡Çµ
void MoveEyeForward::Undo()
{

}

MoveEyeForward::MoveEyeForward(ViewMat* viewMat)
{
    _viewMat = viewMat;
}
MoveEyeForward::MoveEyeForward(){}
MoveEyeForward::~MoveEyeForward(){}