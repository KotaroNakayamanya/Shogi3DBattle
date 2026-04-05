#pragma once

#include"IGameObjFactory.h"

class SilverFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // ã‚Å@çÏê¨ 
};