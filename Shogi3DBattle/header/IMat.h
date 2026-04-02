#pragma once

#include<DirectXMath.h>

class IMat
{
public:
    virtual DirectX::XMMATRIX GetMat() = 0; // s—ñ‚ğ•Ô‚·

    virtual ~IMat() = default;
};