#pragma once

#include"IGameObjFactory.h"

class PieceFactory : public IGameObjFactory
{
protected:
    float _height;
    float _width;

public:
    // pieceçÏê¨
    void CreateGameObj(GameObj* gameObj, GameObj::GameObjType gameObjType, unsigned char objId) override;
};