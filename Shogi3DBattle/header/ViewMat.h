#pragma once

#include<DirectXMath.h>
#include<memory>

class ViewMat
{
private:
    std::unique_ptr<DirectX::XMFLOAT3> _eye;    // 目の位置
    std::unique_ptr<DirectX::XMFLOAT3> _target; // 目線の対象
    std::unique_ptr<DirectX::XMFLOAT3> _up;     // カメラの上側

public:
    DirectX::XMMATRIX GetViewMat(); // ビュー行列を返す
    void RotationY(float y); // y方向に視点を回す

    ViewMat();
    ~ViewMat();
};