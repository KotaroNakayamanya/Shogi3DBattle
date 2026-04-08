#pragma once

#include"I_GameObjFactory.h"

class KingFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<I_GameObj> CreateUniquePtr() override; // â§Å@çÏê¨ 
};