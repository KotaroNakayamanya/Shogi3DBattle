#include"Device11.h"
#include<cassert>
#include"Application.h"

#pragma comment(lib, "d2d1")

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// ラップされたバックバッファ作成
ComPtr<ID3D11Resource> Device11::CreateWrappedBackBuff(ID3D12Resource* buff)
{
    ComPtr<ID3D11Resource> ComPtr;

    D3D11_RESOURCE_FLAGS flags = {};
    flags.BindFlags = D3D11_BIND_RENDER_TARGET;

    _device11->CreateWrappedResource(
        buff,
        &flags,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        IID_PPV_ARGS(ComPtr.ReleaseAndGetAddressOf()));

    return ComPtr;
}

// ラップされたテクスチャバッファ作成
ComPtr<ID3D11Resource> Device11::CreateWrappedTexBuff(ID3D12Resource* buff)
{
    ComPtr<ID3D11Resource> ComPtr;

    D3D11_RESOURCE_FLAGS flags = {};
    flags.BindFlags = D3D11_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;

    _device11->CreateWrappedResource(
        buff,
        &flags,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        IID_PPV_ARGS(ComPtr.ReleaseAndGetAddressOf()));

    return ComPtr;
}




// ラップされたバッファへのレンダリングを許可
void Device11::AcquireWrappedBuff(ID3D11Resource** wrappedBuffAddress)
{
    _device11->AcquireWrappedResources(
        wrappedBuffAddress,
        1); // バックバッファ数 1
}

// ラップされたバッファへのレンダリングをリリース
void Device11::ReleaseWrappedBuff(ID3D11Resource** wrappedBuffAddress)
{
    _device11->ReleaseWrappedResources(
        wrappedBuffAddress,
        1); // バッファ数 1
}




// Direct3D11デバイスセット
void Device11::SetDevice11(ComPtr<ID3D11On12Device> device11){_device11 = device11;}

// Direct3DDeviceをDXGIDeviceとして返す
ComPtr<IDXGIDevice> Device11::GetDXGIDevice()
{
    ComPtr<IDXGIDevice> comPtr;
    _device11.As(&comPtr);

    return comPtr;
}