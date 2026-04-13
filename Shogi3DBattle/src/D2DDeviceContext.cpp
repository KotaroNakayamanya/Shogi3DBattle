#include"D2DDeviceContext.h"
#include"Application.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// Direct2Dレンダーターゲット作成
ComPtr<ID2D1Bitmap1> D2DDeviceContext::CreateD2DRenderTarget(IDXGISurface* dxgiSurface)
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

    

    _d2dDeviceContext->CreateBitmapFromDxgiSurface(
        dxgiSurface,
        &bitmapProps,
        ComPtr.ReleaseAndGetAddressOf());

    return ComPtr;
}

// ブラシ作成 
Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> D2DDeviceContext::CreateBrush(D2D1::ColorF color)
{
    ComPtr<ID2D1SolidColorBrush> comPtr;

    _d2dDeviceContext->CreateSolidColorBrush(
        color,
        comPtr.ReleaseAndGetAddressOf());

    return comPtr;
}



// レンダーターゲットセット
void D2DDeviceContext::SetRenderTarget(ID2D1Bitmap1* d2dRenderTarget)
{
    _d2dDeviceContext->SetTarget(d2dRenderTarget);
}

// 描画開始
void D2DDeviceContext::BeginDraw()
{
    _d2dDeviceContext->BeginDraw();
}

// トランスフォーム
void D2DDeviceContext::SetTransform(D2D1::Matrix3x2F mat)
{
    _d2dDeviceContext->SetTransform(mat);
}

// 描画終了
void D2DDeviceContext::EndDraw()
{
    _d2dDeviceContext->EndDraw();
}

// テキスト描画
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

// 四角形描画
void D2DDeviceContext::DrawRectangle(
    D2D1_RECT_F rect,
    ID2D1Brush* fillBrush,
    ID2D1Brush* strokeBrush)
{
    _d2dDeviceContext->FillRectangle(
        rect,fillBrush
    );

    _d2dDeviceContext->DrawRectangle(
        rect,
        strokeBrush,
        2.0f,
        nullptr);
}

// 2Dテキスト描画
void D2DDeviceContext::DrawText2D(Text2D text2D)
{

    _d2dDeviceContext->DrawTextW(
        text2D.text.c_str(),
        static_cast<UINT32>(text2D.text.length()),
        text2D.textFormat,
        text2D.rect,
        text2D.brush);
}




// Direct2Dデバイスコンテキストセット
void D2DDeviceContext::SetD2DDeviceContext(ComPtr<ID2D1DeviceContext> d2dDeviceContext){_d2dDeviceContext = d2dDeviceContext;}