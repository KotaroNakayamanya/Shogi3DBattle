#pragma once

#include"IGameObjFactory.h"

class BoardFactory : public IGameObjFactory
{
public:
    // «Šû”Õì¬
    void CreateGameObj(GameObj* gameObj, GameObj::GameObjType gameObjType, unsigned char objId) override;
};