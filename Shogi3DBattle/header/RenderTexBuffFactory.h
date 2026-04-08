#pragma once

#include"I_BuffFactory.h"

class RenderTexBuffFactory : public I_BuffFactory
{
public:
    // レンダーテクスチャバッファ作成
    HRESULT CreateBuff(Buff* constBuff, UINT widht, UINT height, ID3D12Device* device) override;

    RenderTexBuffFactory ();
};