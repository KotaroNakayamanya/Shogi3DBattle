#pragma once

#include"IProjMat.h"

class PersProjMat : public IProjMat
{
private:
    float _fov;   // 視野角
    float _ar;    // アスペクト比

public:
    // パースによるプロジェクション行列を返す
    DirectX::XMMATRIX GetMat() override;

    void SetFOV  (float fov);   // 視野角セット
    void SetAR   (float ar);    // アスペクト比セット

    PersProjMat();
    ~PersProjMat();
};