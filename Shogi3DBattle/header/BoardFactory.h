#pragma once

#include"IShogiObjFactory.h"

class BoardFactory : public IShogiObjFactory
{
public:
    // «Šû”Õì¬
    void CreateShogiObj(ShogiObj* shogiObj, GameObj::GameObjType shogiObjType, UCHAR objId) override;
};