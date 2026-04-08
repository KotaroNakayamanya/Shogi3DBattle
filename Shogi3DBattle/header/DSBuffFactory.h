#pragma once

#include"I_BuffFactory.h"

class DSBuffFactory : public I_BuffFactory
{
public:
    // デプスステンシルバッファ作成
    HRESULT CreateBuff(Buff* dsBuff, UINT widht, UINT height, ID3D12Device* device) override;

    DSBuffFactory ();
};