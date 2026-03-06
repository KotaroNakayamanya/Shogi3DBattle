#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

class Device
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Device> _device; // Direct3Dデバイス

public:
    HRESULT CreateDevice(IDXGIAdapter* adapter); // Direct3Dデバイス作成
    ID3D12Device* GetDevice(); // Direct3Dデバイスを渡す

    Device();
    ~Device();
};