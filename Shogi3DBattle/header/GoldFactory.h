#pragma once

#include"IGameObjFactory.h"

class GoldFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // ã‡Å@çÏê¨ 
};