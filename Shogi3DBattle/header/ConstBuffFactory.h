#pragma once

#include"I_BuffFactory.h"

class ConstBuffFactory : public I_BuffFactory
{
public:
    // コンスタントバッファ作成
    HRESULT CreateBuff(Buff* constBuff, UINT widht, UINT height, ID3D12Device* device) override;

    ConstBuffFactory ();
};