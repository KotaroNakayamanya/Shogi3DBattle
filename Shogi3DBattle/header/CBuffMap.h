#pragma once

#include<d3d12.h>
#include<DirectXMath.h>

class CBuffMap
{
private:
    DirectX::XMMATRIX* _cBuffMap; // バッファのマップ

public:
    HRESULT MapCBuff(ID3D12Resource* _cBuff); // コンスタントバッファをマップ
    void RotationY(float pi);

    CBuffMap();
    ~CBuffMap();
};