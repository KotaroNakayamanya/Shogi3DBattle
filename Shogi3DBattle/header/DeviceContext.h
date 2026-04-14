#pragma once

#include<d3d11on12.h>
#include<wrl.h>

class DeviceContext
{
private:
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11DeviceContext> _deviceContext;

public:
    void Flash();

    void SetDeviceContext(ComPtr<ID3D11DeviceContext> deviceContext); // デバイスコンテキストセット
};