#pragma once

#include "IHeapProp.h"

class UploadHeapProp : public IHeapProp
{
public:
    // UPLOADヒーププロパティを返す
    D3D12_HEAP_PROPERTIES GetHeapProp() override;

    UploadHeapProp();
    ~UploadHeapProp();
};