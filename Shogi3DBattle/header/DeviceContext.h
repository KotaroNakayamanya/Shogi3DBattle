#pragma once

#include<d3d11on12.h>
#include<wrl.h>

class DeviceContext
{
private:
    friend class Device;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11DeviceContext> _deviceContext;

public:
    void Flash();

    DeviceContext();
    ~DeviceContext();
};