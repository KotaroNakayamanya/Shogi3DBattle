#pragma once

#include<d3d12.h>
#include<DirectXMath.h>

class CBuffMap
{
private:
    DirectX::XMMATRIX* _cBuffMap; // バッファのマップ

public:
    HRESULT MapCBuff(ID3D12Resource* _cBuff); // コンスタントバッファをマップ

    void WriteMat(DirectX::XMMATRIX mat); // 変換行列を書き込む

    CBuffMap();
    ~CBuffMap();
};