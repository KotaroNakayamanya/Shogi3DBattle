#pragma once

#include<d3d12.h>

class SRV
{
    friend class Device; // Direct3Dデバイスから参照可能

private:
    D3D12_GPU_DESCRIPTOR_HANDLE _srvHandle; // SRVハンドル

public:
    D3D12_GPU_DESCRIPTOR_HANDLE GetSRVHandle(); // SRVハンドルを返す

    SRV();
    ~SRV();
};