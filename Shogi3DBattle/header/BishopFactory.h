#pragma once

#include"I_GameObjFactory.h"

class BishopFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // Šp@ì¬ 
};