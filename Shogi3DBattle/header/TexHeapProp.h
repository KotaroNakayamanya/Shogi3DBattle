#pragma once

#include "IHeapProp.h"

class TexHeapProp : public IHeapProp
{
public:
    // テクスチャヒーププロパティを返す
    D3D12_HEAP_PROPERTIES GetHeapProp() override;
};