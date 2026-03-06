#pragma once

#include<d3d12.h>

class HeapArg
{
public:
    typedef struct CreateCSUHeapArg
    {
        ID3D12Device* device;

        ID3D12Resource* buff1;
        ID3D12Resource* buff2;
        ID3D12Resource* buff3;

    }CreateCSUHeapArg;

    HeapArg(){}
    ~HeapArg(){}
};