#pragma once

#include"Direct2DDevice.h"

class Direct2DFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1Factory3> _direct2DFactory; // Direct2Dファクトリー

public:
    std::unique_ptr<Direct2DDevice> CreateDirect2DDevice(IDXGIDevice* dxgiDevice); // Direct2Dデバイス作成

    Direct2DFactory(ComPtr<ID2D1Factory3>);
};