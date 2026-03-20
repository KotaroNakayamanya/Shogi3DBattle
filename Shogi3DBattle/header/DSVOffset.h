#pragma once

#include"IDescOffset.h"

class DSVOffset : public IDescOffset
{
public:
    // DSVオフセットを返す
    UINT GetDescOffset(ID3D12Device* device) override;

    DSVOffset();
    ~DSVOffset();
};