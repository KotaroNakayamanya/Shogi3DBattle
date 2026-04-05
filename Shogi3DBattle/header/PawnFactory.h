#pragma once

#include"IGameObjFactory.h"

class PawnFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // ï‡Å@çÏê¨ 
};