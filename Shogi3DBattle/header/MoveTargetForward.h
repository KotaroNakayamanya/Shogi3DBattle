#pragma once

#include"MoveCamera.h"

class MoveTargetForward : public MoveCamera
{
public:
    void Exe() override;  // é¿çs
    void Undo() override; // é¿çséÊÇËè¡Çµ

    MoveTargetForward(ViewMat* viewMat);
    MoveTargetForward();
    ~MoveTargetForward();
};