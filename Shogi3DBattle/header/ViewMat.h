#pragma once

#include"IMat.h"
#include<VecCalc.h>

class ViewMat : public IMat
{
private:
    DirectX::XMFLOAT3 _eye;   // 視点位置
    DirectX::XMFLOAT3 _focus; // 注視点位置
    DirectX::XMFLOAT3 _up;    // カメラ上側

public:
    DirectX::XMMATRIX GetMat() override;    // ビュー行列を返す

    void SetEye  (DirectX::XMFLOAT3 eye);   // 視点位置セット
    DirectX::XMFLOAT3 GetEye();             // 視点位置を返す
    void SetFocus(DirectX::XMFLOAT3 focus); // 注視点位置セット
    DirectX::XMFLOAT3 GetFocus();           // 注視点位置を返す
    void SetUp   (DirectX::XMFLOAT3 up);    // カメラ上側ベクトルセット
    DirectX::XMFLOAT3 GetUp();              // カメラ上側ベクトルを返す

    ViewMat();
    ~ViewMat();
};