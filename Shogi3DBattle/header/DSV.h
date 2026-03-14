#pragma once

#include<d3d12.h>

class DSV
{
    friend class Device; // Dierect3Dデバイスから参照可能

private:
    D3D12_CPU_DESCRIPTOR_HANDLE _dsvHandle; // DSVハンドル

public:
    D3D12_CPU_DESCRIPTOR_HANDLE GetDSVHandle(); // DSVハンドルを返す

    DSV();
    ~DSV();
};