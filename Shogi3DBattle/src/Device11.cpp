#include"Device11.h"
#include"Application.h"

#pragma comment(lib, "d2d1")

// Direct2Dデバイスコンテキスト作成
HRESULT Device11::CreateD2DDeviceContext(D2DDeviceContext* d2dDeviceContext)
{
    ComPtr<ID2D1DeviceContext> d2dDeviceContextCom;

    HRESULT result;
    
    // Direct2Dファクトリー作成
    ComPtr<ID2D1Factory3> d2dFactory;
    constexpr D2D1_FACTORY_OPTIONS factoryOptions = {};
    result = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        __uuidof(ID2D1Factory3),
        &factoryOptions,
        reinterpret_cast<void**>(d2dFactory.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    // DXGIデバイス作成
    ComPtr<IDXGIDevice> dxgiDevice;
    result = _device11.As(&dxgiDevice);
    if(FAILED(result)) return result;

    // D2Dデバイス作成
    ComPtr<ID2D1Device> d2dDevice;
    result = d2dFactory->CreateDevice(
        dxgiDevice.Get(),
        d2dDevice.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    result = d2dDevice->CreateDeviceContext(
        D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
        d2dDeviceContextCom.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    d2dDeviceContext->SetD2DDeviceContext(d2dDeviceContextCom);
    return S_OK;
}

// ラップされたバッファ作成
HRESULT Device11::CreateWrappedBuff(
    WrappedBuff* wrappedBuff,
    Buff* buff)
{
    ComPtr<ID3D11Resource> wrappedBuffCom;

    D3D11_RESOURCE_FLAGS flags = {D3D11_BIND_RENDER_TARGET};

    HRESULT result;
    result = _device11->CreateWrappedResource(
        buff->GetBuff(),
        &flags,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        IID_PPV_ARGS(wrappedBuffCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    wrappedBuff->SetWrappedBuff(wrappedBuffCom);
    return S_OK;
}




// ラップされたバッファへのレンダリングを許可
void Device11::AcquireWrappedBuff(WrappedBuff* wrappedBackBuff)
{
    _device11->AcquireWrappedResources(
        wrappedBackBuff->GetWrappedBuffPtr(),
        1); // バックバッファ数 1
}

// ラップされたバッファへのレンダリングをリリース
void Device11::ReleaseWrappedBuff(WrappedBuff* wrappedBackBuffer)
{
    _device11->ReleaseWrappedResources(
        wrappedBackBuffer->GetWrappedBuffPtr(),
        1); // バッファ数 1
}




// Direct3D11デバイスセット
void Device11::SetDevice11(ComPtr<ID3D11On12Device> device11){_device11 = device11;}

Device11::Device11(){}
Device11::~Device11(){}