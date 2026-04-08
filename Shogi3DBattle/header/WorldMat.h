#pragma once

#include"I_Mat.h"
#include"BufferedData.h"

class WorldMat : public I_Mat, public BufferedData<DirectX::XMMATRIX>
{
protected:
    DirectX::XMMATRIX _worldMat;
    
public:
    std::vector<DirectX::XMMATRIX> GetDatas() override; // データ集合を返す
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す

    void SetWorldMat(DirectX::XMMATRIX worldMat); // ワールド行列セット
};