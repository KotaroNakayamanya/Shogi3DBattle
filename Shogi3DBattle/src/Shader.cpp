#include"Shader.h"

#include<cassert>

#pragma comment(lib, "d3dcompiler.lib")

// シェーダーバイナリ作成
HRESULT Shader::CreateShaderBlob()
{
    // 頂点シェーダバイナリ作成
    if (FAILED(CreateVertexShaderBlob()))
    {
        assert(false); return E_FAIL;
    }
    // ピクセルシェーダバイナリ作成
    if (FAILED(CreatePixelShaderBlob()))
    {
        assert(false); return E_FAIL;
    }

    return S_OK;
}

// 頂点シェーダバイナリ作成
HRESULT Shader::CreateVertexShaderBlob()
{
    ComPtr<ID3DBlob> errorBlob;

    return D3DCompileFromFile(
        L"shader/VertexShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VShader",
        "vs_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        _vertexShaderBlob.ReleaseAndGetAddressOf(),
        errorBlob        .ReleaseAndGetAddressOf());
}

// ピクセルシェーダバイナリ作成
HRESULT Shader::CreatePixelShaderBlob()
{
    ComPtr<ID3DBlob> errorBlob;

    return D3DCompileFromFile(
        L"shader/PixelShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PShader",
        "ps_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        _pixelShaderBlob.ReleaseAndGetAddressOf(),
        errorBlob       .ReleaseAndGetAddressOf());
}




// 頂点シェーダーバイナリを渡す
ID3DBlob* Shader::GetVertexShaderBlob()
{
    return _vertexShaderBlob.Get();
}




// ピクセルシェーダーバイナリを渡す
ID3DBlob* Shader::GetPixelShaderBlob()
{
    return _pixelShaderBlob.Get();
}




Shader::Shader(){}
Shader::~Shader(){}