#include"DXGIFactory.h"

#pragma comment(lib, "dxgi.lib")

// DXGIファクトリー作成
HRESULT DXGIFactory::CreateDXGIFactory()
{
    HRESULT result;

    // デバッグモードのときは詳細を表示させるファクトリーを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}




// スワップチェーン作成
HRESULT DXGIFactory::CreateSwapChain(
    SwapChain* swapChain, DXGIFactoryArg::CreateSwapChainArg arg)
{
    
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc(
        arg.windowWidth, arg.windowHeight, arg.rtBuffNum);


    return _dxgiFactory->CreateSwapChainForHwnd(
        arg.commandQueue,
        arg.hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)swapChain->_swapChain.ReleaseAndGetAddressOf());
}

// スワップチェーンディスクリプタ
DXGI_SWAP_CHAIN_DESC1 DXGIFactory::GetSwapChainDesc(
    UINT windowWidth, UINT windowHeight, UINT rtBuffNum)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};

    desc.Width =  // 横の解像度
         windowWidth;
    desc.Height = // 縦の解像度
         windowHeight;
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
        rtBuffNum;
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




// DXGIファクトリを渡す
IDXGIFactory6* DXGIFactory::GetDXGIFactory()
{
    return _dxgiFactory.Get();
}

DXGIFactory::DXGIFactory(){}
DXGIFactory::~DXGIFactory(){}