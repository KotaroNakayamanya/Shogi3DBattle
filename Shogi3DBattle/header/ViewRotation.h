#pragma once

#include"IMouse.h"
#include"ViewMat.h"
#include<DirectXMath.h>

class ViewRotation : public IMouse
{
private:
    ViewMat* _viewMat; // ÉrÉÖÅ[çsóÒ

    void RotationX(float x);
    void RotationY(float y);

public:
    void Exe(int x, int y) override;

    ViewRotation(ViewMat* viewMat);
    ~ViewRotation();
};