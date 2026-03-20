#pragma once

#include "IHeapProp.h"

class DefaultHeapProp : public IHeapProp
{
public:
    // DEFAULTヒーププロパティを返す
    D3D12_HEAP_PROPERTIES GetHeapProp() override;

    DefaultHeapProp();
    ~DefaultHeapProp();
};