#pragma once

#include"D2DRenderTarget.h"
#include"WrappedBuff.h"
#include"Brush.h"
#include<string>

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

    // 黒色ブラシ作成
    HRESULT CreateBlackBrush(Brush* brush);
    // 赤色ブラシ作成
    HRESULT CreateRedBrush(Brush* brush);

    void SetRenderTarget(D2DRenderTarget* d2dRenderTarget);
    void BeginDraw();
    void SetTransform(D2D1::Matrix3x2F mat);
    void EndDraw();

    void DrawTextW(
        std::wstring text,
        D2D1_RECT_F rect,
        IDWriteTextFormat* textFormat,
        ID2D1Brush* brush);

    void SetD2DDeviceContext(ComPtr<ID2D1DeviceContext> d2dDeviceContext); // Direct2Dデバイスコンテキストセット

    D2DDeviceContext();
    ~D2DDeviceContext();
};