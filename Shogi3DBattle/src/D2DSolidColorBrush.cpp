#include"D2DSolicColorBrush.h"

// Direct2Dソリッドカラーブラッシュセット
void D2DSolidColorBrush::SetGetD2DSolidColorBrush(ComPtr<ID2D1SolidColorBrush> d2dSolidColorBrush){_d2dSolidColorBrush = d2dSolidColorBrush;}
// Direct2Dソリッドカラーブラッシュを返す
ID2D1SolidColorBrush* D2DSolidColorBrush::GetD2DSolidColorBrush(){return _d2dSolidColorBrush.Get();}

D2DSolidColorBrush::D2DSolidColorBrush(){}
D2DSolidColorBrush::~D2DSolidColorBrush(){}