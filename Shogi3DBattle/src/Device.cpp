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




// 頂点バッファ作成
HRESULT Device::CreateVertBuff(VertBuff* vertBuffObj, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetResourceDesc(byteSize);

    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(vertBuffObj->_vertBuff.ReleaseAndGetAddressOf()));
}

// ヒーププロパティ
D3D12_HEAP_PROPERTIES Device::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

// リソースディスクリプタ
D3D12_RESOURCE_DESC Device::GetResourceDesc(UINT byteSize)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width =
        byteSize;
    desc.Height =
        1;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count =
        1;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    return desc;
}




// Direct3Dデバイスを渡す
ID3D12Device* Device::GetDevice()
{
    return _device.Get();
}

Device::Device(){}
Device::~Device(){}