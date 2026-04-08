#pragma once

#include"I_GameObjFactory.h"

class BishopFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<I_GameObj> CreateUniquePtr() override; // Šp@ì¬ 
};