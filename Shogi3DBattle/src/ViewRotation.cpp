#include"ViewRotation.h"

void ViewRotation::Exe(int x, int y)
{
    float fx = x / 1000.0f;
    float fy = y / 1000.0f;

    RotationX(fx);
    RotationY(fy);
}

// ƒJƒƒ‰Y‰ñ“]
void ViewRotation::RotationX(float x)
{
    _viewMat->RotationH(x);
}

// ƒJƒƒ‰Y‰ñ“]
void ViewRotation::RotationY(float y)
{
    _viewMat->RotationV(y);
}

ViewRotation::ViewRotation(ViewMat* viewMat)
{
    _viewMat = viewMat;
}
//ViewRotation::ViewRotation(){}
ViewRotation::~ViewRotation(){}