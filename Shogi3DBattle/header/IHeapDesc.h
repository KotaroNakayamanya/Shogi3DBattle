#pragma once

#include<d3d12.h>

class IHeapDesc
{
public:
    // ヒープディスクリプタを返す
    virtual D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(UINT descNum) = 0;

    IHeapDesc() = default;
    ~IHeapDesc(){}
};