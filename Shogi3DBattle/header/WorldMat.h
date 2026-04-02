#pragma once

#include"Mat.h"

class WorldMat : public Mat
{
protected:
    DirectX::XMMATRIX _worldMat;
    
public:
    void SetWorldMat(DirectX::XMMATRIX worldMat); // ワールド行列セット
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す
};