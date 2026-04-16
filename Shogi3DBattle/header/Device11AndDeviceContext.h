#pragma once

#include"Device11.h"
#include<memory>

struct Device11AndDeviceContext
{
    std::unique_ptr<Device11>                   device11;      // DirectX11デバイス
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext; // デバイスコンテキスト
};