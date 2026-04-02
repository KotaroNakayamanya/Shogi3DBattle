#pragma once

#include<d3d12.h>

class IHeapProp
{
public:
    // ヒーププロパティを返す
    virtual D3D12_HEAP_PROPERTIES GetHeapProp() = 0;

    virtual ~IHeapProp() = default;
};