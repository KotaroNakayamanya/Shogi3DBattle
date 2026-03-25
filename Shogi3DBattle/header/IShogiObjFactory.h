#pragma once

#include"ShogiObj.h"

class IShogiObjFactory
{
public:
    // 将棋オブジェクト作成
    virtual void CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, unsigned char objId) = 0;

    IShogiObjFactory() = default;
    ~IShogiObjFactory(){}
};