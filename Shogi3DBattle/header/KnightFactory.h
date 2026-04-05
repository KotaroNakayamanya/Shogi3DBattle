#pragma once

#include"IGameObjFactory.h"

class KnightFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // Œj@ì¬ 
};