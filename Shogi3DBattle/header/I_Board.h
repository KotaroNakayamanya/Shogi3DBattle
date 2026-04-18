#pragma once

#include"I_GameObj.h"

class I_Board : public I_GameObj
{
public:
    I_Board(float size);
    virtual ~I_Board() = default;
};