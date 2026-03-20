#include"D2DDeviceContext.h"
#include"Application.h"

// Direct2Dレンダーターゲット作成
HRESULT D2DDeviceContext::CreateD2DRenderTarget(
    D2DRenderTarget* d2dRenderTarget,
    WrappedBackBuff* wrappedBackBuff)
{
    ComPtr<ID2D1Bitmap1> d2dRenderTargetCom;
    
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
    result = wrappedBackBuff->SetAsDXGISurfaceCom(&dxgiSurface);
    if(FAILED(result)) return result;

    result = _d2dDeviceContext->CreateBitmapFromDxgiSurface(
        dxgiSurface.Get(),
        &bitmapProps,
        d2dRenderTargetCom.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    d2dRenderTarget->SetD2DRenderTarget(d2dRenderTargetCom);
    return S_OK;
}

// ソリッドカラーブラッシュ作成
HRESULT D2DDeviceContext::CreateD2DSolidColorBrush(
    D2DSolidColorBrush* d2dSolidColorBrush)
{
    ComPtr<ID2D1SolidColorBrush> d2dSolidColorBrushCom;

    HRESULT result;
    result = _d2dDeviceContext->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black, 1.0f),
        d2dSolidColorBrushCom.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    d2dSolidColorBrush->SetGetD2DSolidColorBrush(d2dSolidColorBrushCom);
    return S_OK;
}




void D2DDeviceContext::SetRenderTarget(D2DRenderTarget* d2dRenderTarget)
{
    _d2dDeviceContext->SetTarget(d2dRenderTarget->GetD2DRenderTarget());
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




// Direct2Dデバイスコンテキストセット
void D2DDeviceContext::SetD2DDeviceContext(ComPtr<ID2D1DeviceContext> d2dDeviceContext){_d2dDeviceContext = d2dDeviceContext;}

D2DDeviceContext::D2DDeviceContext(){}
D2DDeviceContext::~D2DDeviceContext(){}