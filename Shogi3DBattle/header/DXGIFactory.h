#pragma once

#include"Adapter.h"
#include"Device.h"
#include"SwapChain.h"

#include"DXGIFactoryArg.h"

class DXGIFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリー

    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプタを取得

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc( // スワップチェーンディスクリプタ
        UINT windowWidth, UINT windowHeight, UINT rtBuffNum);

public:
    HRESULT CreateDXGIFactory(); // DXGIファクトリー作成

    HRESULT CreateAdapter(Adapter* adapterObj); // 使用するアダプター作成
    HRESULT CreateDevice(Device* deviceObj, Adapter* adapterObj); // Direct3Dデバイス作成
    HRESULT CreateSwapChain( // スワップチェーン作成
       SwapChain* swapChainObj, DXGIFactoryArg::CreateSwapChainArg arg);

    DXGIFactory();
    ~DXGIFactory();
};