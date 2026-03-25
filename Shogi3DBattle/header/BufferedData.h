#pragma once

#include<d3d12.h>

class BufferedData
{
private:
    D3D12_GPU_VIRTUAL_ADDRESS _buffAddress; // バッファアドレス

public:
    void SetBuffAddress (D3D12_GPU_VIRTUAL_ADDRESS buffAddress); // バッファアドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetBuffAddress();                  // バッファアドレスを返す

    BufferedData();
    ~BufferedData();
};