#include"SwapChain.h"

// スワップチェーン作成
HRESULT SwapChain::CreateSwapChain(
    IDXGIFactory6* dxgiFactory,
    ID3D12CommandQueue* commandQueue,
    HWND hwnd,
    UINT buffNum)
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc(buffNum);

    return dxgiFactory->CreateSwapChainForHwnd(
        commandQueue,
        hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)_swapChain.ReleaseAndGetAddressOf());
}

// スワップチェーンディスクリプタ
DXGI_SWAP_CHAIN_DESC1 SwapChain::GetSwapChainDesc(UINT buffNum)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};

    desc.Width =
        1280;
    desc.Height =
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

// スワップチェーンを返す
IDXGISwapChain4* SwapChain::GetSwapChain()
{
    return _swapChain.Get();
}

SwapChain::SwapChain(){}
SwapChain::~SwapChain(){}