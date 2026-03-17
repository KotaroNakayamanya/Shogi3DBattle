#pragma once

#include"ViewMat.h"

class IMouse
{
public:
    virtual void Exe(int xMove, int yMove) = 0; // ƒ}ƒEƒX‘€ìˆ—

    //IMouse(ViewMat* viewMat){}
    IMouse(){};
    ~IMouse(){};
};