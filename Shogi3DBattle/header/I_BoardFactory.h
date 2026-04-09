#pragma once

#include"B_GameObjFactory.h"
#include"I_Board.h"
#include<memory>

class I_BoardFactory : public B_GameObjFactory
{
public:
    virtual std::unique_ptr<I_Board> CreateBoard() = 0; // «Šû”Õì¬

    virtual ~I_BoardFactory() = default;
};