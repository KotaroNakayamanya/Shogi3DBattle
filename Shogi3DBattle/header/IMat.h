#pragma once

#include<DirectXMath.h>

class IMat
{
public:
    // s—ñ‚ğ•Ô‚·
    virtual DirectX::XMMATRIX GetMat() = 0;

    IMat() = default;
    ~IMat(){}
};