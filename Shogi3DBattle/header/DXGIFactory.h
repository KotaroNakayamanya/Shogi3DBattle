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
    HRESULT CreateAdapter(Adapter* adapter); // 使用するアダプター作成
    HRESULT CreateDevice(Device* device, Adapter* adapter); // Direct3Dデバイス作成
    ComPtr<IDXGISwapChain4> CreateSwapChain(ID3D12CommandQueue* cmdQueue); // スワップチェーン作成

    void SetDXGIFactory(ComPtr<IDXGIFactory6> dxgiFactory); // DXGIファクトリーセット
};