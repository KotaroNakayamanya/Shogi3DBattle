#pragma once

#include"IHeapDesc.h"

class DSVHeapDesc : public IHeapDesc
{
public:
    // DSVヒープディスクリプタを返す
    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(UINT dsvNum) override;

    DSVHeapDesc();
    ~DSVHeapDesc();
};