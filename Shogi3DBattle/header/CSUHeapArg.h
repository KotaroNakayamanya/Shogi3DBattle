#pragma once

class CSUHeapArg
{
public:
    typedef struct CreateCSUHeapArg
    {
        ID3D12Device* device;
        ID3D12Resource* srvBuff;
        ID3D12Resource* cbvBuff;

    }CreateCSUHeapArg;

    CSUHeapArg(){}
    ~CSUHeapArg(){}
};