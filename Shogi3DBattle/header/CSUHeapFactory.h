#pragma once

#include"HeapFactory.h"
#include"CSUHeapDesc.h"
#include"CSUOffset.h"

class CSUHeapFactory : public HeapFactory
{
public:
    //// CSUÉqÅ[ÉvçÏê¨
    //HRESULT CreateHeap(Heap* heap, UINT descNum) override;

    CSUHeapFactory()
    {
        _heapDesc   = std::make_unique<CSUHeapDesc>();
        _descOffset = std::make_unique<CSUOffset>();
    }
    ~CSUHeapFactory(){}
};