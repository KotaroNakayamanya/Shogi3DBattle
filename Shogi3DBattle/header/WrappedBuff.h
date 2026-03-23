#pragma once

#include<d3d11on12.h>
#include<wrl.h>

class WrappedBuff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11Resource> _wrappedBuff; // ラップされたバッファ

public:
    HRESULT SetAsDXGISurfaceCom(ComPtr<IDXGISurface>* dxgiSurfaceComPtr); // DXGIサーフェイスComとしてセットする

    void SetWrappedBuff(ComPtr<ID3D11Resource> wrappedBuff); // ラップされたバッファセット
    ID3D11Resource** GetWrappedBuffPtr(); // ラップされたバッファポインタを返す

    WrappedBuff();
    ~WrappedBuff();
};