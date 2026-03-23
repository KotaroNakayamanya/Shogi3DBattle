#pragma once

#include"IBuffFactory.h"

class RenderTexBuffFactory : public IBuffFactory
{
public:
    // レンダーテクスチャバッファ作成
    HRESULT CreateBuff(Buff* constBuff, UINT widht, UINT height, ID3D12Device* device) override;

    RenderTexBuffFactory();
    ~RenderTexBuffFactory();
};