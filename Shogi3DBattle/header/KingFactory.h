#pragma once

#include"IGameObjFactory.h"

class KingFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // â§Å@çÏê¨ 
};