#pragma once

#include"GameObj.h"

class IGameObjFactory
{
public:
    // ゲームオブジェクト作成
    virtual void CreateGameObj(GameObj* gameObj, GameObj::GameObjType gameObjType, unsigned char objId) = 0;

    virtual ~IGameObjFactory() = default;
};