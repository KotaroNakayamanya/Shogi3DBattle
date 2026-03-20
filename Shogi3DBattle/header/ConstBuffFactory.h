#pragma once

#include"IBuffFactory.h"

class ConstBuffFactory : public IBuffFactory
{
public:
    // コンスタントバッファ作成
    HRESULT CreateBuff(Buff* constBuff, UINT widht, UINT height, ID3D12Device* device) override;

    ConstBuffFactory();
    ~ConstBuffFactory();
};