#pragma once

#include"IGameObjFactory.h"

class BishopFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // Šp@ì¬ 
};