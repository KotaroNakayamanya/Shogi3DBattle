#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

class SwapChain
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGISwapChain4> _swapChain; // スワップチェーン

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc(UINT buffNum); // スワップチェーンディスクリプタ

public:
    HRESULT CreateSwapChain( // スワップチェーン作成
        IDXGIFactory6* dxgiFactory,
        ID3D12CommandQueue* commandQueue,
        HWND hwnd,
        UINT buffNum);

    IDXGISwapChain4* GetSwapChain(); // スワップチェーンを返す

    SwapChain();
    ~SwapChain();
};