#include"WrappedBackBuff.h"

// DXGIサーフェイスComとしてセットする
HRESULT WrappedBackBuff::SetAsDXGISurfaceCom(ComPtr<IDXGISurface>* dxgiSurfaceComPtr)
{
    return _wrappedBackBuff.As(dxgiSurfaceComPtr);
}

// ラップされたバックバッファセット
void WrappedBackBuff::SetWrappedBackBuff(ComPtr<ID3D11Resource> wrappedBackBuff){_wrappedBackBuff = wrappedBackBuff;}
// ラップされたバックバッファポインタを返す
ID3D11Resource** WrappedBackBuff::GetWrappedBackBuffPtr(){return _wrappedBackBuff.GetAddressOf();}

WrappedBackBuff::WrappedBackBuff(){}
WrappedBackBuff::~WrappedBackBuff(){}