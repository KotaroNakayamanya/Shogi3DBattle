#pragma once

#include"Adapter.h"
#include"Device.h"
#include"SwapChain.h"
#include"GameWindow.h"

class DXGIFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリー


    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプタを取得

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc( // スワップチェーンディスクリプタ
        UINT windowWidth, UINT windowHeight, UINT backBuffNum);

public:
    HRESULT CreateAdapter(Adapter* adapter); // 使用するアダプター作成
    HRESULT CreateDevice(Device* device, Adapter* adapter); // Direct3Dデバイス作成
    HRESULT CreateSwapChain( // スワップチェーン作成
        SwapChain* swapChain,
        CmdQueue* cmdQueue,
        GameWindow* gameWindow);

    void SetDXGIFactory(ComPtr<IDXGIFactory6> dxgiFactory); // DXGIファクトリーセット

    DXGIFactory();
    ~DXGIFactory();
};