#include"Direct2DFactory.h"
#include<cassert>

// Direct2Dデバイス作成
std::unique_ptr<Direct2DDevice> Direct2DFactory::CreateDirect2DDevice(IDXGIDevice* dxgiDevice)
{
    ComPtr<ID2D1Device> comPtr;

    HRESULT result;

    result = _direct2DFactory->CreateDevice(
        dxgiDevice,
        comPtr.ReleaseAndGetAddressOf());
        
    assert(SUCCEEDED(result));

    return std::make_unique<Direct2DDevice>(comPtr);
}

Direct2DFactory::Direct2DFactory(ComPtr<ID2D1Factory3> comPtr) : _direct2DFactory(comPtr){}