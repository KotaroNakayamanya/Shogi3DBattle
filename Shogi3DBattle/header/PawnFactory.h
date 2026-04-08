#pragma once

#include"I_GameObjFactory.h"

class PawnFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // ï‡Å@çÏê¨ 
};