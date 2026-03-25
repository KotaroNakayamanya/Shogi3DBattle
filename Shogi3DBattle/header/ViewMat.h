#pragma once

#include<DirectXMath.h>
#include<VecCalc.h>
#include<memory>

class ViewMat
{
private:
    std::unique_ptr<DirectX::XMFLOAT3> _eye;    // 視点
    std::unique_ptr<DirectX::XMFLOAT3> _target; // 視線対象
    std::unique_ptr<DirectX::XMFLOAT3> _up;     // カメラの上側

    DirectX::XMFLOAT3 GetEyeVec(); // eye - target でベクトルを取得

    void CheckUpdateEye(DirectX::XMFLOAT3 eye); // 視点アップデートチェック

public:
    DirectX::XMMATRIX GetViewMat(); // ビュー行列を返す

    DirectX::XMFLOAT3* GetEyePtr();
    DirectX::XMFLOAT3* GetTargetPtr();
    

    void RotationH(float x); // 水平方向に視点を回す
    void RotationV(float y); // 垂直方向に視点を回す
    void MoveEye(float x, float y, float z);    // 視点移動
    void MoveTarget(float x, float y, float z); // 視線対象移動

    ViewMat();
    ~ViewMat();
};