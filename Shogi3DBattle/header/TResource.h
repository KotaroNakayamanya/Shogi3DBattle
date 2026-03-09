#pragma once

#include"d3d12.h"

class TResource
{

public:
    HRESULT WriteTextureToBuff(ID3D12Resource* tBuff); // テクスチャ書き込み

    TResource();
    ~TResource();
};