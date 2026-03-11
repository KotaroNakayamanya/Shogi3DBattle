#include"SwapChain.h"

// スワップチェーン作成
HRESULT SwapChain::CreateSwapChain(
    DrawArg::CreateSwapChainArg arg)
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc(
        arg.width, arg.height, arg.buffNum);

    return arg.dxgiFactory->CreateSwapChainForHwnd(
        arg.commandQueue,
        arg.hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)_swapChain.ReleaseAndGetAddressOf());
}

// スワップチェーンディスクリプタ
DXGI_SWAP_CHAIN_DESC1 SwapChain::GetSwapChainDesc(
    UINT width, UINT height, UINT buffNum)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};

    desc.Width =  // 横の解像度
         1280;
    desc.Height = // 縦の解像度
         720;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo =
        false;
    desc.SampleDesc.Count =
        1;
    desc.SampleDesc.Quality =
        0;
    desc.BufferUsage =
        DXGI_USAGE_BACK_BUFFER;
    desc.BufferCount =
        buffNum;

    desc.Scaling =
        DXGI_SCALING_STRETCH;
    desc.SwapEffect =
        DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode =
        DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags =
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    return desc;
}

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