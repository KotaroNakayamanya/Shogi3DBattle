#pragma once

#include<d2d1_3.h>
#include<wrl.h>

class Brush
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID2D1SolidColorBrush> _brush; // ブラシ
    
public:
    void SetBrush(ComPtr<ID2D1SolidColorBrush> d2dSolidColorBrush); // ブラシセット
    ID2D1SolidColorBrush* GetBrush();                               // ブラシを返す

    Brush();
    ~Brush();
};