#pragma once

#include<d3d11on12.h>
#include<wrl.h>

class WrappedBackBuff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11Resource> _wrappedBackBuff;

public:
    HRESULT SetAsDXGISurfaceCom(ComPtr<IDXGISurface>* dxgiSurfaceComPtr); // DXGIサーフェイスComとしてセットする

    void SetWrappedBackBuff(ComPtr<ID3D11Resource> wrappedBackBuff); // ラップされたバックバッファセット
    ID3D11Resource** GetWrappedBackBuffPtr(); // ラップされたバックバッファポインタを返す

    WrappedBackBuff();
    ~WrappedBackBuff();
};