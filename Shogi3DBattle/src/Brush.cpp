#include"Brush.h"

void Brush::SetBrush(ComPtr<ID2D1SolidColorBrush> brush){_brush = brush;}      // ブラシセット
ID2D1SolidColorBrush* Brush::GetBrush()                 {return _brush.Get();} // ブラシを返す

Brush::Brush(){}
Brush::~Brush(){}