#pragma once

#include"HeapFactory.h"
#include"RTVHeapDesc.h"
#include"RTVOffset.h"

class RTVHeapFactory : public HeapFactory
{
public:
    //// RTVÉqÅ[ÉvçÏê¨
    //HRESULT CreateHeap(Heap* heap, UINT descNum) override;

    RTVHeapFactory()
    {
        _heapDesc   = std::make_unique<RTVHeapDesc>();
        _descOffset = std::make_unique<RTVOffset>();
    }
    ~RTVHeapFactory(){}
};