#pragma once

#include"I_WorldMat.h"
#include"B_BufferedData.h"

class WorldMat : public I_WorldMat, public B_BufferedData
{
protected:
    DirectX::XMMATRIX _worldMat;
    
public:
    // I_WorldMat, I_Mat
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す

    // I_WorldMat
    void SetMat(DirectX::XMMATRIX worldMat) override; // ワールド行列セット
    
    // B_BufferedData
    HRESULT WriteToBuff(Buff* buff) override; // バッファに書き込み
    unsigned int GetSize() override; // サイズ取得

};