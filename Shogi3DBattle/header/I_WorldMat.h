#pragma once

#include"I_Mat.h"

class I_WorldMat : public I_Mat
{
public:
    virtual void SetMat(DirectX::XMMATRIX worldMat) = 0; // ワールド行列セット
    
    // I_Mat
    virtual DirectX::XMMATRIX GetMat() = 0; // ワールド行列を返す

    virtual ~I_WorldMat() = default;
};