#pragma once

#include"ShogiObj.h"

class IShogiObjFactory
{
public:
    // 将棋オブジェクト作成
    virtual void CreateShogiObj(ShogiObj* shogiObj, GameObj::GameObjType shogiObjType, unsigned char objId) = 0;

    virtual ~IShogiObjFactory() = default;
};