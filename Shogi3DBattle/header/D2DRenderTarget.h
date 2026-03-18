#pragma once

#include<d2d1_3.h>
#include<wrl.h>

class D2DRenderTarget
{
    friend class D2DDeviceContext;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1Bitmap1> _d2dRenderTarget;

public:
    D2DRenderTarget(){}
    ~D2DRenderTarget(){}
};