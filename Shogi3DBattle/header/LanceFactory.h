#pragma once

#include"IGameObjFactory.h"

class LanceFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // @ì¬ 
};