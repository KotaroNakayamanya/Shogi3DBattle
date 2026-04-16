#include"Direct2DDeviceContext.h"
#include"Application.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// Direct2Dレンダーターゲット作成
ComPtr<ID2D1Bitmap1> Direct2DDeviceContext::CreateD2DRenderTarget(IDXGISurface* dxgiSurface)
{
    ComPtr<ID2D1Bitmap1> ComPtr;
    
    // dpi取得
    auto gameWindow = Application::GetInstance().GetGameWindow();
    auto dpi = GetDpiForWindow(gameWindow->GetHWND());

    D2D1_BITMAP_PROPERTIES1 bitmapProps =
        D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(
                DXGI_FORMAT_UNKNOWN,
                D2D1_ALPHA_MODE_PREMULTIPLIED),
            static_cast<float>(dpi),
            static_cast<float>(dpi));

    

    _direct2DDeviceContext->CreateBitmapFromDxgiSurface(
        dxgiSurface,
        &bitmapProps,
        ComPtr.ReleaseAndGetAddressOf());

    return ComPtr;
}

// ブラシ作成 
Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> Direct2DDeviceContext::CreateBrush(D2D1::ColorF color)
{
    ComPtr<ID2D1SolidColorBrush> comPtr;

    _direct2DDeviceContext->CreateSolidColorBrush(
        color,
        comPtr.ReleaseAndGetAddressOf());

    return comPtr;
}



// レンダーターゲットセット
void Direct2DDeviceContext::SetRenderTarget(ID2D1Bitmap1* d2dRenderTarget)
{
    _direct2DDeviceContext->SetTarget(d2dRenderTarget);
}

// 描画開始
void Direct2DDeviceContext::BeginDraw()
{
    _direct2DDeviceContext->BeginDraw();
}

// トランスフォーム
void Direct2DDeviceContext::SetTransform(D2D1::Matrix3x2F mat)
{
    _direct2DDeviceContext->SetTransform(mat);
}

// 描画終了
void Direct2DDeviceContext::EndDraw()
{
    _direct2DDeviceContext->EndDraw();
}

// テキスト描画
void Direct2DDeviceContext::DrawTextW(
    std::wstring text,
    D2D1_RECT_F rect,
    IDWriteTextFormat* textFormat,
    ID2D1Brush* brush)
{
    _direct2DDeviceContext->DrawTextW(
        text.c_str(),
        static_cast<UINT32>(text.length()),
        textFormat,
        rect,
        brush);
}

// 四角形描画
void Direct2DDeviceContext::DrawRectangle(
    D2D1_RECT_F rect,
    ID2D1Brush* fillBrush,
    ID2D1Brush* strokeBrush)
{
    _direct2DDeviceContext->FillRectangle(
        rect,fillBrush
    );

    _direct2DDeviceContext->DrawRectangle(
        rect,
        strokeBrush,
        2.0f,
        nullptr);
}

// 2Dテキスト描画
void Direct2DDeviceContext::DrawText2D(Text2D text2D)
{

    _direct2DDeviceContext->DrawTextW(
        text2D.text.c_str(),
        static_cast<UINT32>(text2D.text.length()),
        text2D.textFormat,
        text2D.rect,
        text2D.brush);
}




// Direct2Dデバイスコンテキストセット
void Direct2DDeviceContext::SetDirect2DDeviceContext(ComPtr<ID2D1DeviceContext> direct2DDeviceContext){_direct2DDeviceContext = direct2DDeviceContext;}

Direct2DDeviceContext::Direct2DDeviceContext(ComPtr<ID2D1DeviceContext> comPtr) : _direct2DDeviceContext(comPtr){}