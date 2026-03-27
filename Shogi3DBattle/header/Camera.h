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

    void SetCameraPos(DirectX::XMFLOAT3 pos); // カメラ位置セット
    void MoveCameraPos(DirectX::XMFLOAT3 vec); // カメラ移動

    void SetFocusPos(DirectX::XMFLOAT3 pos); // フォーカス位置セット
    void MoveFocusPos (DirectX::XMFLOAT3 vec); // フォーカス位置移動

    DirectX::XMFLOAT3 GetNormLookVec(); // 正規化された視線ベクトルを返す

    DirectX::XMMATRIX GetViewProjMat(); // ビュープロジェクション行列を返す

    void SetViewMat(ViewMat* viewMat); // ビュー行列セット
    ViewMat* GetViewMat();             // ビュー行列を返す
    void SetProjMat(ProjMat* projMat); // プロジェクション行列セット
    ProjMat* GetProjMat();             // プロジェクション行列を返す

    Camera();
    ~Camera();
};