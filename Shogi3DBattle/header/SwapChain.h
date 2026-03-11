#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

#include"DrawArg.h"

class SwapChain
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    friend class DXGIFactory; // DXGIFactoryから参照可能

private:
    ComPtr<IDXGISwapChain4> _swapChain; // スワップチェーン

public:
    UINT GetCurrentBackBufferIdx(); // 現在のバックバッファインデックスを返す
    void Flip(); // 画面フリップ
    HRESULT UpdateSwapChain(UINT width, UINT height); // スワップチェーン更新
    IDXGISwapChain4* GetSwapChain(); // スワップチェーンを返す

    SwapChain();
    ~SwapChain();
};