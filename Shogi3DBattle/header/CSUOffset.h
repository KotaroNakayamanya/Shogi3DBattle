#pragma once

#include"IDescOffset.h"

class CSUOffset : public IDescOffset
{
public:
    // CSUオフセットを返す
    UINT GetDescOffset(ID3D12Device* device) override;

    CSUOffset();
    ~CSUOffset();
};