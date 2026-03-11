#pragma once

#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>

class Adapter
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    friend class DXGIFactory; // DXGIファクトリから参照可能

private:
    ComPtr<IDXGIAdapter> _adapter; // 使用するアダプター

public:
    void SetAdapterComPtr(ComPtr<IDXGIAdapter>); // 使用するアダプタをセットする
    IDXGIAdapter* GetAdapter(); // 使用するアダプタを渡す

    Adapter();
    ~Adapter();
};