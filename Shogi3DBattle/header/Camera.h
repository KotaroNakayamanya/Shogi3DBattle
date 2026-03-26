#pragma once

#include"ViewMat.h"
#include"ProjMat.h"

class Camera
{
private:
    std::unique_ptr<ViewMat> _viewMat; // ビュー行列
    std::unique_ptr<ProjMat> _projMat; // プロジェクション行列

public:
    void RotationH(float x); // 水平方向に視点を回す
    void RotationV(float y); // 垂直方向に視点を回す

    void MoveCamera(DirectX::XMFLOAT3 vec); // カメラ移動
    void MoveFocus (DirectX::XMFLOAT3 vec); // 注視点位置移動

    DirectX::XMMATRIX GetViewProjMat(); // ビュープロジェクション行列を返す

    void SetViewMat(ViewMat* viewMat); // ビュー行列セット
    ViewMat* GetViewMat();             // ビュー行列を返す
    void SetProjMat(ProjMat* projMat); // プロジェクション行列セット
    ProjMat* GetProjMat();             // プロジェクション行列を返す

    Camera();
    ~Camera();
};