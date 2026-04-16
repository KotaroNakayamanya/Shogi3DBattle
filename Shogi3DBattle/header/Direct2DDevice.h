#pragma once

#include"Direct2DDeviceContext.h"
#include<memory>

class Direct2DDevice
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1Device> _direct2DDevice; // Direct2Dデバイス

public:
    std::unique_ptr<Direct2DDeviceContext> CreateDirect2DDeviceContext(); // Direct2Dデバイスコンテキスト作成

    Direct2DDevice(ComPtr<ID2D1Device> comPtr);
};