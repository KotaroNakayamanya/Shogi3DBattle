#pragma once

#include"I_GameObjFactory.h"

class KnightFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<I_GameObj> CreateUniquePtr() override; // Œj@ì¬ 
};