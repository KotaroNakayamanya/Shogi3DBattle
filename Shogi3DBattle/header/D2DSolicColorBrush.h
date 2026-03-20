#pragma once

#include<d2d1_3.h>
#include<wrl.h>

class D2DSolidColorBrush
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1SolidColorBrush> _d2dSolidColorBrush; // Direct2Dソリッドカラーブラッシュ
    
public:
    void SetGetD2DSolidColorBrush(ComPtr<ID2D1SolidColorBrush> d2dSolidColorBrush); // Direct2Dソリッドカラーブラッシュセット
    ID2D1SolidColorBrush* GetD2DSolidColorBrush(); // Direct2Dソリッドカラーブラッシュを返す

    D2DSolidColorBrush();
    ~D2DSolidColorBrush();
};