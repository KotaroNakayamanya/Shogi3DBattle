#pragma once

#include"IHeapDesc.h"

class CSUHeapDesc : public IHeapDesc
{
public:
    // CSUヒープディスクリプタを返す
    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(UINT csuNum) override;

    CSUHeapDesc();
    ~CSUHeapDesc();
};