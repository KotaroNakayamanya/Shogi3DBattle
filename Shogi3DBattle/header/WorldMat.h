#pragma once

#include"I_WorldMat.h"
#include"B_BufferedData.h"

class WorldMat : public I_WorldMat, public B_BufferedData
{
protected:
    DirectX::XMMATRIX _mat; // ワールド行列
    
public:
    void              SetMat(DirectX::XMMATRIX worldMat) override; // ワールド行列セット
    DirectX::XMMATRIX GetMat() override; // ワールド行列を返す
    
    HRESULT WriteToBuff(Buff* buff) override; // バッファに書き込み

    unsigned int GetSize() override; // サイズ取得

};