#pragma once

#include<DirectXMath.h>
#include<memory>

class ProjMat
{
private:
    std::unique_ptr<DirectX::XMMATRIX> _projMat;

public:
    DirectX::XMMATRIX GetProjMat();

    ProjMat();
    ~ProjMat();
};