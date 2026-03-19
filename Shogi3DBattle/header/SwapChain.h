#pragma once

#include<dxgi1_6.h>
#include<wrl.h>

class SwapChain
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDXGISwapChain4> _swapChain; // スワップチェーン

public:
    UINT GetCurrentBackBufferIdx(); // 現在のバックバッファインデックスを返す
    void Flip(); // 画面フリップ
    HRESULT UpdateSwapChain(UINT width, UINT height); // スワップチェーン更新
    UINT GetBackBuffNum(); // バックバッファ数を返す

    void SetSwapChain(ComPtr<IDXGISwapChain4> swapChain); // スワップチェーンセット
    IDXGISwapChain4* GetSwapChain(); // スワップチェーンを返す
    

    SwapChain();
    ~SwapChain();
};