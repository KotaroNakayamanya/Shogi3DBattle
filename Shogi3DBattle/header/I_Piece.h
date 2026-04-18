#pragma once

#include"I_GameObj.h"
#include<DirectXMath.h>

class I_Piece : public I_GameObj
{
public:
    void Move(DirectX::XMFLOAT3 vec); // ˆÚ“®

    I_Piece(float mmBottomWidth, float mmHeight);
    virtual ~I_Piece() = default;
};