#pragma once

#include"IBuffFactory.h"

class TexBuffFactory : public IBuffFactory
{
public:
    // テクスチャバッファ作成
    HRESULT CreateBuff(Buff* constBuff, UINT widht, UINT height, ID3D12Device* device) override;

    TexBuffFactory();
    ~TexBuffFactory();
};