#pragma once

class HeapArg
{
public:
    typedef struct CreateHeapArg
    {
        ID3D12Device* device;
        ID3D12Resource* srvBuff;
        ID3D12Resource* cbvBuff;

    }CreateHeapArg;
};