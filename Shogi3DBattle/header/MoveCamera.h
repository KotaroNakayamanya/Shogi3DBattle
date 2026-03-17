#pragma once

#include"ICommand.h"
#include"ViewMat.h"

class MoveCamera : public ICommand
{
protected:
    ViewMat* _viewMat;

public:
    MoveCamera(ViewMat* viewMat) : _viewMat(viewMat){}
    MoveCamera() = default;
    ~MoveCamera(){}
};