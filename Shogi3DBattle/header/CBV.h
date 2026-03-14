#pragma once

#include<d3d12.h>

class CBV
{
    friend class Device; // Direct3Dデバイスから参照可能

public:
    D3D12_GPU_DESCRIPTOR_HANDLE _cbvHandle; // CBVハンドル

public:
    D3D12_GPU_DESCRIPTOR_HANDLE GetCBVHandle(); // CBVハンドルを返す

    CBV();
    ~CBV();
};