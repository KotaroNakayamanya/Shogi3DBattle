#pragma once

#include"IHeapDesc.h"

class RTVHeapDesc : public IHeapDesc
{
public:
    // RTVヒープディスクリプタを返す
    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(UINT rtvNum) override;

    RTVHeapDesc();
    ~RTVHeapDesc();
};