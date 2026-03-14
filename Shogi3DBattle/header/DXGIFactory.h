#pragma once

//#include<memory>
#include"Adapter.h"
#include"Device.h"
#include"SwapChain.h"
#include"GameWindow.h"

#include"DXGIFactoryArg.h"

class DXGIFactory
{
    friend class DX12; // DX12クラスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリー


    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプタを取得

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc( // スワップチェーンディスクリプタ
        UINT windowWidth, UINT windowHeight, UINT rtBuffNum);

public:
    HRESULT CreateAdapter(Adapter* adapterObj); // 使用するアダプター作成
    HRESULT CreateDevice(Device* deviceObj, Adapter* adapterObj); // Direct3Dデバイス作成
    //HRESULT CreateSwapChain(SwapChain* swapChain, DXGIFactoryArg::CreateSwapChainArg arg); // スワップチェーン作成
    HRESULT CreateSwapChain( // スワップチェーン作成
        SwapChain* swapChain,
        ComQueue* comQueue,
        GameWindow* gameWindow);



    DXGIFactory();
    ~DXGIFactory();
};