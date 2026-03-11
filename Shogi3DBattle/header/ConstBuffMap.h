#pragma once

#include<d3d12.h>
#include<DirectXMath.h>

class ConstBuffMap
{
private:
    DirectX::XMMATRIX* _constBuffMap; // バッファのマップ

public:
    HRESULT MapCBuff(ID3D12Resource* _constBuff); // コンスタントバッファをマップ

    void WriteMat( // 変換行列を書き込む
        DirectX::XMMATRIX worldMat,
        DirectX::XMMATRIX viewMat,
        DirectX::XMMATRIX projMat);

    ConstBuffMap();
    ~ConstBuffMap();
};