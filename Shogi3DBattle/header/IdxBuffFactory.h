#pragma once

#include"I_BuffFactory.h"

class IdxBuffFactory : public I_BuffFactory
{
public:
    // インデックスバッファ作成
    HRESULT CreateBuff(Buff* idxBuff, UINT widht, UINT height, ID3D12Device* device) override;

    IdxBuffFactory();
    ~IdxBuffFactory() = default;
};