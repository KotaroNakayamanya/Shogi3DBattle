#pragma once

#include<d2d1_3.h>
#include<wrl.h>

class D2DRenderTarget
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1Bitmap1> _d2dRenderTarget; // Direct2Dレンダーターゲット

public:
    void SetD2DRenderTarget(ComPtr<ID2D1Bitmap1> d2dRenderTarget); // Direct2Dレンダーターゲットセット
    ID2D1Bitmap1* GetD2DRenderTarget(); // Direct2Dレンダーターゲットを返す

    D2DRenderTarget();
    ~D2DRenderTarget();
};