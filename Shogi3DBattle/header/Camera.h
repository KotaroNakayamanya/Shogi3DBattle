#pragma once

#include"I_BufferedData.h"
#include"ViewMat.h"
#include"I_ProjMat.h"
#include<memory>

class Camera : public I_BufferedData
{
private:
    std::unique_ptr<ViewMat>   _viewMat; // ビュー行列
    std::unique_ptr<I_ProjMat> _projMat; // プロジェクション行列

public:
    void SetCameraPos(DirectX::XMFLOAT3 pos);   // カメラ位置セット
    DirectX::XMFLOAT3 GetCameraPos();           // カメラ位置を返す
    void SetFocusPos(DirectX::XMFLOAT3 pos);    // フォーカス位置セット
    DirectX::XMFLOAT3 GetFocusPos();            // フォーカス位置を返す
    void SetCameraUpVec(DirectX::XMFLOAT3 vec); // カメラ上側ベクトルセット
    DirectX::XMFLOAT3 GetCameraUpVec();         // カメラ上側ベクトルを返す
    
    void MoveCameraPos(DirectX::XMFLOAT3 vec); // カメラ移動
    void MoveFocusPos (DirectX::XMFLOAT3 vec); // フォーカス位置移動メラ上側ベクトルを返す

    void RotationH(float x); // 水平方向に視点を回す
    void RotationV(float y); // 垂直方向に視点を回す

    DirectX::XMFLOAT3 GetNormLookVec(); // 正規化された視線ベクトルを返す
    
    void WriteToBuff(ID3D12Resource* buff) override; // バッファに書き込み
    
    ViewMat* GetViewMat();               // ビュー行列を返す
    void SetProjMat(I_ProjMat* projMat); // プロジェクション行列セット
    I_ProjMat* GetProjMat();                 // プロジェクション行列を返す

    Camera(std::unique_ptr<ViewMat> viewMat, std::unique_ptr<I_ProjMat> projMat);
};