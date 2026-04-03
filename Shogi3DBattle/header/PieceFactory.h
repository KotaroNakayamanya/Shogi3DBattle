#pragma once

#include"IShogiObjFactory.h"

class PieceFactory : public IShogiObjFactory
{
protected:
    float _height;
    float _width;

public:
    // pieceçÏê¨
    void CreateShogiObj(ShogiObj* shogiObj, GameObj::GameObjType shogiObjType, UCHAR objId) override;
};