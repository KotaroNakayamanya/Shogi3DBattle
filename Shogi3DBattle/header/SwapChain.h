#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"DrawArg.h"

class SwapChain
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGISwapChain4> _swapChain; // スワップチェーン

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc( // スワップチェーンディスクリプタ
        UINT width, UINT height, UINT buffNum);

public:
    HRESULT CreateSwapChain( // スワップチェーン作成
        DrawArg::CreateSwapChainArg arg);

    UINT GetCurrentBackBufferIdx(); // 現在のバックバッファインデックスを返す

    void Flip(); // 画面フリップ

    HRESULT UpdateSwapChain(UINT width, UINT height); // スワップチェーン更新

    IDXGISwapChain4* GetSwapChain(); // スワップチェーンを返す

    SwapChain();
    ~SwapChain();
};