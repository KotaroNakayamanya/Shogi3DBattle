#pragma once

#include"I_GameObjFactory.h"

class RookFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<I_GameObj> CreateUniquePtr() override; // ”ò@ì¬ 
};