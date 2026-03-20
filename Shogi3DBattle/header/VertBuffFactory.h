#pragma once

#include"IBuffFactory.h"

class VertBuffFactory : public IBuffFactory
{
public:
    // 頂点バッファ作成
    HRESULT CreateBuff(Buff* vertBuff, UINT widht, UINT height, ID3D12Device* device) override;

    VertBuffFactory();
    ~VertBuffFactory();
};