#pragma once

#include"I_HeapFactory.h"
#include"DSVHeapDesc.h"
#include"DSVOffset.h"

class DSVHeapFactory : public I_HeapFactory
{
public:
    DSVHeapFactory()
    {
        _heapDesc   = std::make_unique<DSVHeapDesc>();
        _descOffset = std::make_unique<DSVOffset>();
    }
    ~DSVHeapFactory(){}
};