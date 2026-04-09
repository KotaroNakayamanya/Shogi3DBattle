#pragma once

#include"I_Mat.h"

class I_WorldMat : public I_Mat
{
public:
    virtual void SetMat(DirectX::XMMATRIX worldMat) = 0; // ワールド行列セット

    virtual ~I_WorldMat() = default;
};