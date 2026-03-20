#pragma once

#include"Buff.h"
#include"Heap.h"

class IViewFactory
{
public:
    // ƒrƒ…[ì¬
    virtual void CreateView(Heap* heap, UINT i, Buff* buff, ID3D12Device* device) = 0;

    IViewFactory() = default;
    ~IViewFactory(){}
};