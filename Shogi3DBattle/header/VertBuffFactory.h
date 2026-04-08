#pragma once

#include"I_BuffFactory.h"

class VertBuffFactory : public I_BuffFactory
{
public:
    // 頂点バッファ作成
    HRESULT CreateBuff(Buff* vertBuff, UINT widht, UINT height, ID3D12Device* device) override;

    VertBuffFactory ();
};