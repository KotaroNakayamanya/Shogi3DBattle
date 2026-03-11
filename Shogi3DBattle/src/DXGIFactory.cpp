#include"DXGIFactory.h"
#include<string>
#include<array>

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
    SwapChain* swapChainObj, DXGIFactoryArg::CreateSwapChainArg arg)
{
    
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc(
        arg.windowWidth, arg.windowHeight, arg.rtBuffNum);


    return _dxgiFactory->CreateSwapChainForHwnd(
        arg.commandQueue,
        arg.hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)swapChainObj->_swapChain.ReleaseAndGetAddressOf());
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




// 使用するアダプター作成
HRESULT DXGIFactory::CreateAdapter(Adapter* adapterObj)
{
    // 探索対象のアダプター名
    std::array<std::wstring, 3> adapterNames =
    {
        L"NVIDIA",
        L"AMD",
        L"Intel"
    };

    // 使用可能なアダプターを取得
    std::vector<ComPtr<IDXGIAdapter>> canUseAdapters =
        GetCanUseAdapters();
    // 使用可能なアダプターがなければ失敗を返す
    if(canUseAdapters.size() == 0) return E_FAIL;
    

    for(auto& adapter : canUseAdapters)
    {
        // アダプター名取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapter->GetDesc(&adapterDesc);
        std::wstring descStr = adapterDesc.Description;

        // リストに存在するアダプターであれば利用する
        auto it = std::find(adapterNames.begin(), adapterNames.begin(), descStr);
        if (it != adapterNames.end())
        {
            adapterObj->_adapter = adapter;
            goto complete;
        }
    }

    // 見つからなければ一番最初のアダプターを利用する
    adapterObj->_adapter = canUseAdapters[0];

complete:
    return S_OK;
}


template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 使用可能なアダプターを取得
std::vector<ComPtr<IDXGIAdapter>> DXGIFactory::GetCanUseAdapters()
{
    std::vector<ComPtr<IDXGIAdapter>> adapters;
    ComPtr<IDXGIAdapter> tmpAdapter;
    
    int i = 0;
    while (_dxgiFactory->EnumAdapters(i, tmpAdapter.ReleaseAndGetAddressOf())
           != DXGI_ERROR_NOT_FOUND)
    {
        adapters.push_back(tmpAdapter);
        i++;
    }

    return adapters;
}




DXGIFactory::DXGIFactory(){}
DXGIFactory::~DXGIFactory(){}