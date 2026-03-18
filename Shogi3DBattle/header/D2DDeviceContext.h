#pragma once

#include"D2DRenderTarget.h"
#include"WrappedBackBuffer.h"
#include"D2DSolicColorBrush.h"
#include<string>

class D2DDeviceContext
{
    friend class Device11;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1DeviceContext> _d2dDeviceContext;
    
public:
    // Direct2Dレンダーターゲット作成
    HRESULT CreateD2DRenderTarget(
        D2DRenderTarget* d2dRenderTarget,
        WrappedBackBuffer* wrappedBackBuffer);

    // ソリッドカラーブラッシュ作成
    HRESULT CreateD2DSolidColorBrush(
        D2DSolidColorBrush* d2dSolidColorBrush);

    void SetRenderTarget(D2DRenderTarget* d2dRenderTarget);
    void BeginDraw();
    void SetTransform(D2D1::Matrix3x2F mat);
    void EndDraw();

    void DrawTextW(
        std::wstring text,
        D2D1_RECT_F rect,
        IDWriteTextFormat* textFormat,
        ID2D1Brush* brush);

    D2DDeviceContext();
    ~D2DDeviceContext();
};