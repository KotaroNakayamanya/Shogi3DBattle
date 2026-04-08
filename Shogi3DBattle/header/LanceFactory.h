#pragma once

#include"I_GameObjFactory.h"

class LanceFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // @ì¬ 
};