#include"ConstBuffMap.h"

// コンスタントバッファをマップ
HRESULT ConstBuffMap::MapCBuff(ID3D12Resource* _constBuff)
{
    return _constBuff->Map(0, nullptr, (void**)&_constBuffMap);
}

// 変換行列を書き込む
void ConstBuffMap::WriteMat(
    DirectX::XMMATRIX worldMat,
    DirectX::XMMATRIX viewMat,
    DirectX::XMMATRIX projMat)
{
    *_constBuffMap = worldMat * viewMat * projMat;
}

ConstBuffMap::ConstBuffMap(){}
ConstBuffMap::~ConstBuffMap(){}