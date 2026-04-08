#pragma once

#include"I_BuffFactory.h"

class TexBuffFactory : public I_BuffFactory
{
public:
    // テクスチャバッファ作成
    HRESULT CreateBuff(Buff* constBuff, UINT widht, UINT height, ID3D12Device* device) override;

    TexBuffFactory ();
};