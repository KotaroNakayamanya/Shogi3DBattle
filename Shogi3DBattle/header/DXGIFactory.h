#pragma once

#include"Adapter.h"
#include"Device.h"
#include"GameWindow.h"

class DXGIFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリー


    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプタを取得

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc(GameWindow* gameWindow); // スワップチェーンディスクリプタ

public:
    ComPtr<IDXGIAdapter> GetAdapter(); // 使用するアダプターを返す
    ComPtr<IDXGISwapChain4> CreateSwapChain(ID3D12CommandQueue* cmdQueue); // スワップチェーン作成

    DXGIFactory();
};