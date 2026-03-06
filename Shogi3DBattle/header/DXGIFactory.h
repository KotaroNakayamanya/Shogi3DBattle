#pragma once

#include<dxgi1_6.h>
#include<wrl.h>

class DXGIFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリー

public:
    HRESULT CreateDXGIFactory(); // DXGIファクトリー作成
    IDXGIFactory6* GetDXGIFactory(); // DXGIファクトリーを渡す

    DXGIFactory();
    ~DXGIFactory();
};