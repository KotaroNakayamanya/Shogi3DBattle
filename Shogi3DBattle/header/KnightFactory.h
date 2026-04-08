#pragma once

#include"I_GameObjFactory.h"

class KnightFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // Œj@ì¬ 
};