#include"ViewMat.h"
#include<cmath>

// ビュー行列を返す
DirectX::XMMATRIX ViewMat::GetMat()
{
    return DirectX::XMMatrixLookAtLH(
        DirectX::XMLoadFloat3(&_eye),
        DirectX::XMLoadFloat3(&_focus),
        DirectX::XMLoadFloat3(&_up));
}

void ViewMat::SetEye  (DirectX::XMFLOAT3 eye)   {_eye   = eye;}   // 視点位置セット
DirectX::XMFLOAT3 ViewMat::GetEye()             {return _eye;}    // 視点位置を返す
void ViewMat::SetFocus(DirectX::XMFLOAT3 focus) {_focus = focus;} // 注視点位置セット
DirectX::XMFLOAT3 ViewMat::GetFocus()           {return _focus;}  // 注視点位置を返す
void ViewMat::SetUp   (DirectX::XMFLOAT3 up)    {_up    = up;}    // カメラ上側ベクトルセット
DirectX::XMFLOAT3 ViewMat::GetUp()              {return _up;}     // カメラ上側ベクトルを返す

ViewMat::ViewMat(){}
ViewMat::~ViewMat(){}