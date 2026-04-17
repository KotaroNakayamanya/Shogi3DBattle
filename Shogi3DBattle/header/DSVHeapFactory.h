#pragma once

#include"I_HeapFactory.h"
#include"DSVHeapDesc.h"
#include"DSVOffset.h"

class DSVHeapFactory : public I_HeapFactory
{
public:
    // DSVÉqÅ[ÉvçÏê¨
    //HRESULT CreateHeap(Heap* heap, UINT descNum);

    DSVHeapFactory()
    {
        _heapDesc   = std::make_unique<DSVHeapDesc>();
        _descOffset = std::make_unique<DSVOffset>();
    }
    ~DSVHeapFactory(){}
};