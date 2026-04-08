#pragma once

#include"I_GameObjFactory.h"

class SilverFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<I_GameObj> CreateUniquePtr() override; // ã‚Å@çÏê¨ 
};