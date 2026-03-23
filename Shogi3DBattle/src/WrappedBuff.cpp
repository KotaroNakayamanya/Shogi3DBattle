#include"WrappedBuff.h"

// DXGIサーフェイスComとしてセットする
HRESULT WrappedBuff::SetAsDXGISurfaceCom(ComPtr<IDXGISurface>* dxgiSurfaceComPtr)
{
    return _wrappedBuff.As(dxgiSurfaceComPtr);
}

// ラップされたバックバッファセット
void WrappedBuff::SetWrappedBuff(ComPtr<ID3D11Resource> wrappedBuff){_wrappedBuff = wrappedBuff;}
// ラップされたバックバッファポインタを返す
ID3D11Resource** WrappedBuff::GetWrappedBuffPtr(){return _wrappedBuff.GetAddressOf();}

WrappedBuff::WrappedBuff(){}
WrappedBuff::~WrappedBuff(){}