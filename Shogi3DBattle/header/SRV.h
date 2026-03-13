#pragma once

#include<d3d12.h>

class SRV
{
    friend class Device; // Direct3Dデバイスから参照可能

private:
    D3D12_CPU_DESCRIPTOR_HANDLE _srvHandle; // SRVハンドル

public:
    SRV();
    ~SRV();
};