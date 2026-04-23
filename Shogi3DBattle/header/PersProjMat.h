#pragma once

#include"I_ProjMat.h"

class PersProjMat : public I_ProjMat
{
private:
    float _fov; // 視野角
    float _ar;  // アスペクト比

public:
    DirectX::XMMATRIX GetMat() override; // パースによるプロジェクション行列を返す

    void SetFOV  (float fov);   // 視野角セット
    void SetAR   (float ar);    // アスペクト比セット

    PersProjMat(
        float fov   = DirectX::XM_PIDIV2,
        float ar    = 16.0f / 9.0f,
        float nearZ =  1.0f,
        float farZ  = 50.0f);
};