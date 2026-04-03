#pragma once

#include"GameObj.h"

class Piece : public GameObj
{
public:     
    void Move(DirectX::XMFLOAT3 vec); // x²•ûŒü‚É“®‚­‚æ‚¤‚Éƒ[ƒ‹ƒhs—ñ‚ğ•ÏŠ·‚·‚é

    Piece();
    ~Piece();
};