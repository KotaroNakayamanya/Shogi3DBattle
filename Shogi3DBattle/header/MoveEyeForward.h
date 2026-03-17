#pragma once

#include"MoveCamera.h"

class MoveEyeForward : public MoveCamera
{
public:
    void Exe() override;  // é¿çs
    void Undo() override; // é¿çséÊÇËè¡Çµ

    MoveEyeForward(ViewMat* viewMat);
    MoveEyeForward();
    ~MoveEyeForward();
};