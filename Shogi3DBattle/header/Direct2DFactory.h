#pragma once

#include<d2d1_3.h>
#include<wrl.h>
#include<memory>

class Direct2DFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1Factory3> _direct2DFactory; // Direct2Dファクトリー

public:
    std::unique_ptr<ID2D1Device> CreateDirect2DDevice(IDXGIDevice* dxgiDevice); // Direct2Dデバイス作成
};