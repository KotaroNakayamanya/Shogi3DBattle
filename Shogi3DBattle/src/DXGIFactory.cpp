#include"DXGIFactory.h"
#include<string>
#include<array>

#pragma comment(lib, "d3d12.lib")

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 使用するアダプター作成
HRESULT DXGIFactory::CreateAdapter(Adapter* adapter)
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
    

    for(auto& adapterCom : canUseAdapters)
    {
        // アダプター名取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapterCom->GetDesc(&adapterDesc);
        std::wstring descStr = adapterDesc.Description;

        // リストに存在するアダプターであれば利用する
        auto it = std::find(adapterNames.begin(), adapterNames.begin(), descStr);
        if (it != adapterNames.end())
        {
            adapter->SetAdapter(adapterCom);
            goto complete;
        }
    }

    // 見つからなければ一番最初のアダプターを利用する
    adapter->SetAdapter(canUseAdapters[0]);

complete:
    return S_OK;
}

// 使用可能なアダプターのリストを取得
std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> DXGIFactory::GetCanUseAdapters()
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

// スワップチェーン作成
ComPtr<IDXGISwapChain4> DXGIFactory::CreateSwapChain(
    ID3D12CommandQueue* cmdQueue,
    GameWindow* gameWindow)
{
    ComPtr<IDXGISwapChain4> comPtr;

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc(
        gameWindow->GetWindowWidth(), gameWindow->GetWindowHeight(), 2);

    _dxgiFactory->CreateSwapChainForHwnd(
        cmdQueue,
        gameWindow->GetHWND(),
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)comPtr.ReleaseAndGetAddressOf());

    return comPtr;
}

// スワップチェーンディスクリプタ
DXGI_SWAP_CHAIN_DESC1 DXGIFactory::GetSwapChainDesc(
    UINT windowWidth, UINT windowHeight, UINT backBuffNum)
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
        backBuffNum;
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




// Direct3Dデバイス作成
HRESULT DXGIFactory::CreateDevice(Device* device, Adapter* adapter)
{
    ComPtr<ID3D12Device> deviceCom;

    std::array<D3D_FEATURE_LEVEL, 5> featureLevels = // GPU機能レベルを列挙
    {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };

    // GPU機能レベルの配列順にデバイス作成を試みる
    HRESULT result;
    auto it = std::find_if(featureLevels.begin(), featureLevels.end(),
        [&deviceCom, &result, &adapter](D3D_FEATURE_LEVEL featureLevel)
        {
            result = D3D12CreateDevice(
                adapter->GetAdapter(),
                featureLevel,
                IID_PPV_ARGS(deviceCom.ReleaseAndGetAddressOf()));

            return result == S_OK; // 作成できたら戻る
        });

    if(it == featureLevels.end()) return result; // エラー

    device->SetDevice(deviceCom);
    return S_OK;;
}

void DXGIFactory::SetDXGIFactory(ComPtr<IDXGIFactory6> dxgiFactory){_dxgiFactory = dxgiFactory;} // DXGIファクトリーセット