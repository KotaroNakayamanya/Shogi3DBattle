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

    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters( // 使用可能なアダプターを取得
        IDXGIFactory6* dxgiFactory);

public:
    HRESULT CreateAdapter(IDXGIFactory6* dxgiFactory); // 使用するアダプター作成
    IDXGIAdapter* GetAdapter(); // 使用するアダプターを渡す

    Adapter();
    ~Adapter();
};