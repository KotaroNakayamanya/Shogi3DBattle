#include"Device.h"
#include<array>
#include<cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

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




template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// シェーダーオブジェクト作成
HRESULT Device::CreateShaderObj(Shader* shaderObj)
{
    if (FAILED(CreateVShaderBlob(shaderObj))) goto failed; // 頂点シェーダバイナリ作成
    if (FAILED(CreatePShaderBlob(shaderObj))) goto failed; // ピクセルシェーダバイナリ作成

    return S_OK;

failed:
    assert(false);
    return E_FAIL;
}

// 頂点シェーダバイナリ作成
HRESULT Device::CreateVShaderBlob(Shader* shaderObj)
{
    ComPtr<ID3DBlob> errBlob;

    return D3DCompileFromFile(
        L"shader/VertexShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VShader",
        "vs_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        shaderObj->_vShaderBlob.ReleaseAndGetAddressOf(),
        errBlob                .ReleaseAndGetAddressOf());
}

// ピクセルシェーダバイナリ作成
HRESULT Device::CreatePShaderBlob(Shader* shaderObj)
{
    ComPtr<ID3DBlob> errBlob;

    return D3DCompileFromFile(
        L"shader/PixelShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PShader",
        "ps_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        shaderObj->_pShaderBlob.ReleaseAndGetAddressOf(),
        errBlob                .ReleaseAndGetAddressOf());
}




// Direct3Dデバイスを渡す
ID3D12Device* Device::GetDevice()
{
    return _device.Get();
}

Device::Device(){}
Device::~Device(){}