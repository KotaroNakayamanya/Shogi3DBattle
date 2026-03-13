#pragma once

#include<DirectXMath.h>
#include<memory>

class ViewMat
{
private:
    std::unique_ptr<DirectX::XMFLOAT3> _eye;    // 視点
    std::unique_ptr<DirectX::XMFLOAT3> _target; // 視線対象
    std::unique_ptr<DirectX::XMFLOAT3> _up;     // カメラの上側

    DirectX::XMFLOAT3 GetEyeVec(); // eye - target でベクトルを取得

    void CheckUpdateEye(DirectX::XMFLOAT3 eye); // 視点アップデートチェック

    DirectX::XMFLOAT3 GetNormFloat3( // 正規化
        DirectX::XMFLOAT3 f);

    DirectX::XMFLOAT3 GetFloat3AddFloat3( // XMFLOAT3 + XMFLOAT3
        DirectX::XMFLOAT3 f1,
        DirectX::XMFLOAT3 f2);

    DirectX::XMFLOAT3 GetFloat3SubFloat3( // XMFLOAT3 - XMFLOAT3
        DirectX::XMFLOAT3 f1,
        DirectX::XMFLOAT3 f2);

    DirectX::XMFLOAT3 GetFloat3MulMat( // XMFLOAT3 * XMMATRIX
        DirectX::XMFLOAT3 f,
        DirectX::XMMATRIX mat);

    DirectX::XMFLOAT3 GetFloat3FromVec( // XMVECTOR → XMFLOAT3
        DirectX::XMVECTOR v);

public:
    DirectX::XMMATRIX GetViewMat(); // ビュー行列を返す

    void RotationH(float x); // 水平方向に視点を回す
    void RotationV(float y); // 垂直方向に視点を回す

    ViewMat();
    ~ViewMat();
};