#pragma once

#include"IGameObjFactory.h"

class BoardFactory : public IGameObjFactory
{
public:
    std::unique_ptr<GameObj> CreateUniquePtr() override; // «Šû”Õì¬
};