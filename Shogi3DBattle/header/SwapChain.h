#pragma once

#include<dxgi1_6.h>
#include<wrl.h>

class SwapChain
{
    friend class DXGIFactory; // DXGIファクトリから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGISwapChain4> _swapChain; // スワップチェーン
    UINT _rtBuffNum = 2; // レンダーターゲットバッファ数

public:
    UINT GetCurrentBackBufferIdx(); // 現在のバックバッファインデックスを返す
    void Flip(); // 画面フリップ
    HRESULT UpdateSwapChain(UINT width, UINT height); // スワップチェーン更新

    IDXGISwapChain4* GetSwapChain(); // スワップチェーンを返す
    UINT GetRTBuffNum(); // レンダーターゲットバッファ数を返す

    SwapChain();
    ~SwapChain();
};