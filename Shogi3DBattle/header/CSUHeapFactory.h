#pragma once

#include"I_HeapFactory.h"
#include"CSUHeapDesc.h"
#include"CSUOffset.h"

class CSUHeapFactory : public I_HeapFactory
{
public:
    CSUHeapFactory()
    {
        _heapDesc   = std::make_unique<CSUHeapDesc>();
        _descOffset = std::make_unique<CSUOffset>();
    }
    ~CSUHeapFactory(){}
};