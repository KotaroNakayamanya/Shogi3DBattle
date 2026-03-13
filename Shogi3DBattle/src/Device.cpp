#include"Device.h"
#include<d3dcompiler.h>
#include<cassert>

#pragma comment(lib, "d3dcompiler.lib")

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