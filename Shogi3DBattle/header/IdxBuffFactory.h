#pragma once

#include"IBuffFactory.h"

class IdxBuffFactory : public IBuffFactory
{
public:
    // インデックスバッファ作成
    HRESULT CreateBuff(Buff* idxBuff, UINT widht, UINT height, ID3D12Device* device) override;

    IdxBuffFactory();
    ~IdxBuffFactory() = default;
};