#include"D2DRenderTarget.h"

// Direct2Dレンダーターゲットセット
void D2DRenderTarget::SetD2DRenderTarget(ComPtr<ID2D1Bitmap1> d2dRenderTarget){_d2dRenderTarget = d2dRenderTarget;}
// Direct2Dレンダーターゲットを返す
ID2D1Bitmap1* D2DRenderTarget::GetD2DRenderTarget(){return _d2dRenderTarget.Get();}

D2DRenderTarget::D2DRenderTarget(){}
D2DRenderTarget::~D2DRenderTarget(){}