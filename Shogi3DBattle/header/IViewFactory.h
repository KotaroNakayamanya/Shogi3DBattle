#pragma once

#include"Heap.h"

class IViewFactory
{
public:
    // ƒrƒ…[ì¬
    virtual void CreateView(Heap* heap, UINT i, ID3D12Resource* buff, ID3D12Device* device) = 0;

    virtual ~IViewFactory() = default;
};