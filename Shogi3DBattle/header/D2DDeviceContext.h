#pragma once

#include"D2DRenderTarget.h"
#include"WrappedBuff.h"
#include<string>
#include"Text2D.h"

class D2DDeviceContext
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1DeviceContext> _d2dDeviceContext;
    
public:
    // Direct2Dレンダーターゲット作成
    HRESULT CreateD2DRenderTarget(
        D2DRenderTarget* d2dRenderTarget,
        WrappedBuff* wrappedBuff);

    ComPtr<ID2D1SolidColorBrush> CreateBrush(D2D1::ColorF color); // ブラシ作成

    void SetRenderTarget(D2DRenderTarget* d2dRenderTarget); // レンダーターゲットセット
    void BeginDraw();                                       // 描画開始
    void SetTransform(D2D1::Matrix3x2F mat);
    void EndDraw();                                         // 描画終了

    void DrawTextW( // テキスト描画
        std::wstring text,
        D2D1_RECT_F rect,
        IDWriteTextFormat* textFormat,
        ID2D1Brush* brush);

    void DrawText2D(Text2D text2D); // 2Dテキスト描画

    void DrawRectangle( // 四角形描画
        D2D1_RECT_F rect,
        ID2D1Brush* fillBrush,
        ID2D1Brush* strokeBrush);

    void SetD2DDeviceContext(ComPtr<ID2D1DeviceContext> d2dDeviceContext); // Direct2Dデバイスコンテキストセット

    D2DDeviceContext();
    ~D2DDeviceContext();
};