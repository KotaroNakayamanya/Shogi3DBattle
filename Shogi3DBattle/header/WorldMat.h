#pragma once

#include"I_Mat.h"
#include"BufferedData.h"

class WorldMat : public I_Mat, public BufferedData
{
protected:
    DirectX::XMMATRIX _worldMat;
    
public:
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す
    
    // バッファに書き込み
    HRESULT WriteToBuff(Buff* buff) override;

    unsigned int GetSize() override;

    void SetWorldMat(DirectX::XMMATRIX worldMat); // ワールド行列セット
};