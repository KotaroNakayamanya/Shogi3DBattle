#pragma once

#include<d3d12.h>

class CBV
{
    friend class Device; // Direct3Dデバイスから参照可能

public:
    D3D12_CPU_DESCRIPTOR_HANDLE _cbvHandle; // CBVハンドル

public:
    CBV();
    ~CBV();
};