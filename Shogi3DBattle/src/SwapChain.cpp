#include"SwapChain.h"

// 現在のバックバッファインデックスを返す
UINT SwapChain::GetCurrentBackBufferIdx()
{
    return _swapChain->GetCurrentBackBufferIndex();
}

// スワップチェーン更新
HRESULT SwapChain::UpdateSwapChain(UINT width, UINT height)
{
    return _swapChain->ResizeBuffers(
        0,
        0,
        0,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

    return S_OK;
}




// 画面フリップ
void SwapChain::Flip()
{
    _swapChain->Present(1, 0);
}




// スワップチェーンを返す
IDXGISwapChain4* SwapChain::GetSwapChain(){return _swapChain.Get();}




SwapChain::SwapChain(){}
SwapChain::~SwapChain(){}