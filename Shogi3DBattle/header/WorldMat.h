#pragma once

#include"IMat.h"

class WorldMat : public IMat
{
private:
    DirectX::XMMATRIX _worldMat;
    
public:
    void SetWorldMat(DirectX::XMMATRIX worldMat); // ワールド行列セット
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す

    WorldMat();
    ~WorldMat();
};