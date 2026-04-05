#pragma once

#include"IGameObjFactory.h"

class RookFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // ”ò@ì¬ 
};