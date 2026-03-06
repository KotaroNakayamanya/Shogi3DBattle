#include"Device.h"

#include<array>

#pragma comment(lib, "d3d12.lib")

// Direct3Dデバイス作成
HRESULT Device::CreateDevice(IDXGIAdapter* adapter)
{
    // GPU機能レベル一覧
    std::array<D3D_FEATURE_LEVEL, 5> featureLevels =
    {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };

    // GPU機能レベルの配列順にデバイス作成を試みる
    HRESULT result;
    std::find_if(featureLevels.begin(), featureLevels.end(),
        [this, &result, adapter](D3D_FEATURE_LEVEL featureLevel)
        {
            result = D3D12CreateDevice(
                //adapter.Get(),
                adapter,
                featureLevel,
                IID_PPV_ARGS(_device.ReleaseAndGetAddressOf()));

            return result == S_OK; // 作成できたら戻る
        });

    return result;
}

// Direct3Dデバイスを渡す
ID3D12Device* Device::GetDevice()
{
    return _device.Get();
}

Device::Device(){}
Device::~Device(){}