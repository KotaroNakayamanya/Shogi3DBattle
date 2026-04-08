#pragma once

#include<DirectXMath.h>

class I_Mat
{
public:
    virtual DirectX::XMMATRIX GetMat() = 0; // s—ñ‚ğ•Ô‚·

    virtual ~I_Mat() = default;
};