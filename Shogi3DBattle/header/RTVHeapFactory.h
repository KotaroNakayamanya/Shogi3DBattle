#pragma once

#include"I_HeapFactory.h"
#include"RTVHeapDesc.h"
#include"RTVOffset.h"

class RTVHeapFactory : public I_HeapFactory
{
public:
    RTVHeapFactory()
    {
        _heapDesc   = std::make_unique<RTVHeapDesc>();
        _descOffset = std::make_unique<RTVOffset>();
    }
};