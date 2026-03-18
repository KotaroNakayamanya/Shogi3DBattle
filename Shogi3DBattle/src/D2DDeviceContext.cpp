#include"D2DDeviceContext.h"
#include"Application.h"

// Direct2Dレンダーターゲット作成
HRESULT D2DDeviceContext::CreateD2DRenderTarget(
    D2DRenderTarget* d2dRenderTarget,
    WrappedBackBuffer* wrappedBackBuffer)
{
    
    HWND hwnd = Application::GetInstance().GetHWND();
    const UINT dpi = GetDpiForWindow(hwnd);
    D3D11_RESOURCE_FLAGS flags = {D3D11_BIND_RENDER_TARGET};
    D2D1_BITMAP_PROPERTIES1 bitmapProps =
        D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(
                DXGI_FORMAT_UNKNOWN,
                D2D1_ALPHA_MODE_PREMULTIPLIED),
            static_cast<float>(dpi),
            static_cast<float>(dpi));

    HRESULT result;

    // DXGIサーフェイス作成
    ComPtr<IDXGISurface> dxgiSurface;
    result = wrappedBackBuffer->_wrappedBackBuffer.As(&dxgiSurface);
    if(FAILED(result)) return result;

    return _d2dDeviceContext->CreateBitmapFromDxgiSurface(
        dxgiSurface.Get(),
        &bitmapProps,
        d2dRenderTarget->_d2dRenderTarget.ReleaseAndGetAddressOf());
}

// ソリッドカラーブラッシュ作成
HRESULT D2DDeviceContext::CreateD2DSolidColorBrush(
    D2DSolidColorBrush* d2dSolidColorBrush)
{
    return _d2dDeviceContext->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black, 1.0f),
        d2dSolidColorBrush->_d2dSolidColorBrush.ReleaseAndGetAddressOf());
}




void D2DDeviceContext::SetRenderTarget(D2DRenderTarget* d2dRenderTarget)
{
    _d2dDeviceContext->SetTarget(d2dRenderTarget->_d2dRenderTarget.Get());
}

void D2DDeviceContext::BeginDraw()
{
    _d2dDeviceContext->BeginDraw();
}

void D2DDeviceContext::SetTransform(D2D1::Matrix3x2F mat)
{
    _d2dDeviceContext->SetTransform(mat);
}

void D2DDeviceContext::EndDraw()
{
    _d2dDeviceContext->EndDraw();
}

void D2DDeviceContext::DrawTextW(
    std::wstring text,
    D2D1_RECT_F rect,
    IDWriteTextFormat* textFormat,
    ID2D1Brush* brush)
{
    _d2dDeviceContext->DrawTextW(
        text.c_str(),
        static_cast<UINT32>(text.length()),
        textFormat,
        rect,
        brush);
}




D2DDeviceContext::D2DDeviceContext(){}
D2DDeviceContext::~D2DDeviceContext(){}