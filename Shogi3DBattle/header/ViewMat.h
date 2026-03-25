#pragma once

#include"IMat.h"
#include<VecCalc.h>

class ViewMat : public IMat
{
private:
    DirectX::XMFLOAT3 _eye;   // 視点位置
    DirectX::XMFLOAT3 _focus; // 注視点位置
    DirectX::XMFLOAT3 _up;    // カメラ上側

    void CheckUpdateEye(DirectX::XMFLOAT3 eye); // 視点アップデートチェック

public:
    // ビュー行列を返す
    DirectX::XMMATRIX GetMat() override;

    void RotationH(float x); // 水平方向に視点を回す
    void RotationV(float y); // 垂直方向に視点を回す
    void MoveEye(float x, float y, float z);    // 視点位置移動
    void MoveFocus(float x, float y, float z);  // 注視点位置移動

    void SetEye  (float x, float y, float z); // 視点位置セット
    void SetFocus(float x, float y, float z); // 注視点位置セット
    void SetUp   (float x, float y, float z); // カメラ上側セット

    ViewMat();
    ~ViewMat();
};