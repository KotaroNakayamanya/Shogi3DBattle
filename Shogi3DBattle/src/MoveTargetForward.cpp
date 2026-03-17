#include"MoveTargetForward.h"

// é¿çs
void MoveTargetForward::Exe()
{
    //_viewMat->MoveTargetForward(0.1f);
}

// é¿çséÊÇËè¡Çµ
void MoveTargetForward::Undo()
{

}

MoveTargetForward::MoveTargetForward(ViewMat* viewMat) : MoveCamera(viewMat){}
MoveTargetForward::MoveTargetForward(){}
MoveTargetForward::~MoveTargetForward(){}