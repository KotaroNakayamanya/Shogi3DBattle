#pragma once

#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>

class Adapter
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIAdapter> _adapter; // 使用するアダプター

public:
    void SetAdapter(ComPtr<IDXGIAdapter> adapter); // 使用するアダプターセット
    IDXGIAdapter* GetAdapter(); // 使用するアダプタを返す

    Adapter();
    ~Adapter();
};