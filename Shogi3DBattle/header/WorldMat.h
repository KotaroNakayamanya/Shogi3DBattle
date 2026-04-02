#pragma once

#include"IMat.h"
#include"BufferedData.h"

class WorldMat : public IMat, public BufferedData<DirectX::XMMATRIX>
{
protected:
    DirectX::XMMATRIX _worldMat;
    
public:
    std::vector<DirectX::XMMATRIX> GetDatas() override; // データ集合を返す

    void SetWorldMat(DirectX::XMMATRIX worldMat); // ワールド行列セット
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す
};