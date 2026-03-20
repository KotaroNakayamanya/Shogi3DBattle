#pragma once

#include"IBuffFactory.h"

class DSBuffFactory : public IBuffFactory
{
public:
    // デプスステンシルバッファ作成
    HRESULT CreateBuff(Buff* dsBuff, UINT widht, UINT height, ID3D12Device* device) override;

    DSBuffFactory();
    ~DSBuffFactory();
};