#pragma once

#include"IShogiObjFactory.h"

class PieceFactory : public IShogiObjFactory
{
protected:
    float _height;
    float _width;

public:
    // pieceçÏê¨
    void CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UINT id) override;

    PieceFactory() = default;
    ~PieceFactory();
};