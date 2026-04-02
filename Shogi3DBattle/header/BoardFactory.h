#pragma once

#include"IShogiObjFactory.h"

class BoardFactory : public IShogiObjFactory
{
public:
    // è´ä˚î’çÏê¨
    void CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UCHAR objId) override;

    BoardFactory () = default;
    ~BoardFactory() = default;
};