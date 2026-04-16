#include"Direct2DDevice.h"
#include<cassert>

// Direct2Dデバイスコンテキスト作成
std::unique_ptr<Direct2DDeviceContext> Direct2DDevice::CreateDirect2DDeviceContext()
{
    ComPtr<ID2D1DeviceContext> comPtr;

    HRESULT result;

    result = _direct2DDevice->CreateDeviceContext(
        D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
        comPtr.ReleaseAndGetAddressOf());

    assert(SUCCEEDED(result));

    return std::make_unique<Direct2DDeviceContext>(comPtr);
}

Direct2DDevice::Direct2DDevice(ComPtr<ID2D1Device> comPtr) : _direct2DDevice(comPtr){}
