#pragma once

#include"IDescOffset.h"

class RTVOffset : public IDescOffset
{
public:
    // RTVオフセットを返す
    UINT GetDescOffset(ID3D12Device* device) override;

    RTVOffset();
    ~RTVOffset();
};