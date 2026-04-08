#pragma once

#include"I_GameObjFactory.h"

class BoardFactory : public I_GameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // «Šû”Õì¬
};