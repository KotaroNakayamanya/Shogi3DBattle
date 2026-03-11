#pragma once

#include<dxgi1_6.h>
#include<wrl.h>

#include"SwapChain.h"

#include"DXGIFactoryArg.h"

class DXGIFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリー

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc( // スワップチェーンディスクリプタ
        UINT windowWidth, UINT windowHeight, UINT rtBuffNum);

public:
    HRESULT CreateDXGIFactory(); // DXGIファクトリー作成
    IDXGIFactory6* GetDXGIFactory(); // DXGIファクトリーを渡す

   HRESULT CreateSwapChain( // スワップチェーン作成
       SwapChain* swapChain, DXGIFactoryArg::CreateSwapChainArg arg);

    DXGIFactory();
    ~DXGIFactory();
};