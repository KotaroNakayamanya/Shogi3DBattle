#pragma once

#include"I_BoardFactory.h"
#include"B_GameObjFactory.h"

class B_BoardFactory : public I_BoardFactory, public B_GameObjFactory
{
public:
    virtual std::unique_ptr<I_Board> CreateBoard() = 0; // «Šû”Õì¬
};