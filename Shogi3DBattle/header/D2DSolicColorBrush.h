#pragma once

#include<d2d1_3.h>
#include<wrl.h>

class D2DSolidColorBrush
{
    friend class D2DDeviceContext;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1SolidColorBrush> _d2dSolidColorBrush;
    
public:
    ID2D1SolidColorBrush* GetD2DSolidColorBrush(){return _d2dSolidColorBrush.Get();}

    D2DSolidColorBrush(){}
    ~D2DSolidColorBrush(){}
};