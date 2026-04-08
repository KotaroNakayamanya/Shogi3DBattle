#pragma once

#include"BufferedData.h"
#include"ViewMat.h"
#include"I_Mat.h"
#include<memory>

class Camera : public BufferedData
{
private:
    std::unique_ptr<ViewMat> _viewMat; // ビュー行列
    std::unique_ptr<I_Mat>    _projMat; // プロジェクション行列

public:
    DirectX::XMMATRIX GetViewProjMat(); // ビュープロジェクション行列を返す

    void RotationH(float x); // 水平方向に視点を回す
    void RotationV(float y); // 垂直方向に視点を回す

    void SetCameraPos(DirectX::XMFLOAT3 pos);   // カメラ位置セット
    DirectX::XMFLOAT3 GetCameraPos();           // カメラ位置を返す
    void SetFocusPos(DirectX::XMFLOAT3 pos);    // フォーカス位置セット
    DirectX::XMFLOAT3 GetFocusPos();            // フォーカス位置を返す
    void SetCameraUpVec(DirectX::XMFLOAT3 vec); // カメラ上側ベクトルセット
    DirectX::XMFLOAT3 GetCameraUpVec();         // カメラ上側ベクトルを返す


    void MoveFocusPos (DirectX::XMFLOAT3 vec); // フォーカス位置移動
    void MoveCameraPos(DirectX::XMFLOAT3 vec); // カメラ移動

    DirectX::XMFLOAT3 GetNormLookVec(); // 正規化された視線ベクトルを返す
    
    // バッファに書き込み
    HRESULT WriteToBuff(Buff* buff) override;

    unsigned int GetSize() override;
    

    


    void SetViewMat(ViewMat* viewMat); // ビュー行列セット
    ViewMat* GetViewMat();             // ビュー行列を返す
    void SetProjMat(I_Mat* projMat);    // プロジェクション行列セット
    I_Mat* GetProjMat();                // プロジェクション行列を返す
};