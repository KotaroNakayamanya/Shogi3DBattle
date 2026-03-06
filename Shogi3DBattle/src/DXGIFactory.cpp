#include"DXGIFactory.h"

#pragma comment(lib, "dxgi.lib")

// DXGIファクトリー作成
HRESULT DXGIFactory::CreateDXGIFactory()
{
    HRESULT result;

    // デバッグモードのときは詳細を表示させるファクトリーを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}

// DXGIファクトリを渡す
IDXGIFactory6* DXGIFactory::GetDXGIFactory()
{
    return _dxgiFactory.Get();
}

DXGIFactory::DXGIFactory(){}
DXGIFactory::~DXGIFactory(){}