#pragma once

#include"I_Mat.h"
#include"I_BufferedData.h"

class WorldMat : public I_Mat, public I_BufferedData
{
protected:
    DirectX::XMMATRIX _mat; // ワールド行列
    
public:
    void              SetMat(DirectX::XMMATRIX worldMat); // ワールド行列セット
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す
    
    void WriteToBuff(ID3D12Resource* buff) override; // バッファに書き込み

    WorldMat();
};