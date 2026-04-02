#pragma once

#include<d3d12.h>

class BuffData
{
private:
    D3D12_GPU_VIRTUAL_ADDRESS _buffAddress; // バッファアドレス

public:
    void SetBuffAddress (D3D12_GPU_VIRTUAL_ADDRESS buffAddress){_buffAddress = buffAddress;} // バッファアドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetBuffAddress()                 {return _buffAddress;}                  // バッファアドレスを返す

    virtual ~BuffData() = default;
};