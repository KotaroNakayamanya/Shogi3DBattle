#include"Device11.h"
#include<cassert>
#include"Application.h"

#pragma comment(lib, "d2d1")

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// Direct2Dデバイスコンテキスト作成
std::unique_ptr<D2DDeviceContext> Device11::CreateD2DDeviceContext()
{

    HRESULT result;
    
    // Direct2Dファクトリー作成
    ComPtr<ID2D1Factory3> d2dFactory;

    result = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        __uuidof(ID2D1Factory3),
        nullptr,
        reinterpret_cast<void**>(d2dFactory.ReleaseAndGetAddressOf()));

    assert(SUCCEEDED(result));

    // DXGIデバイス作成
    ComPtr<IDXGIDevice> dxgiDevice;
    result = _device11.As(&dxgiDevice);
    assert(SUCCEEDED(result));

    // D2Dデバイス作成
    ComPtr<ID2D1Device> d2dDevice;
    result = d2dFactory->CreateDevice(
        dxgiDevice.Get(),
        d2dDevice.ReleaseAndGetAddressOf());
    assert(SUCCEEDED(result));


    ComPtr<ID2D1DeviceContext> comPtr;

    result = d2dDevice->CreateDeviceContext(
        D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
        comPtr.ReleaseAndGetAddressOf());
    assert(SUCCEEDED(result));

    return std::make_unique<D2DDeviceContext>(comPtr);
}

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

Device11::Device11(){}
Device11::~Device11(){}