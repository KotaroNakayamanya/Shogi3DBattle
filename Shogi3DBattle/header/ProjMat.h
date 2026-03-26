#pragma once

#include"IMat.h"
#include<memory>

class ProjMat : public IMat
{
private:
    float _fov;   // 視野角
    float _ar;    // アスペクト比
    float _nearZ; // クリッピング手前側距離
    float _farZ;  // クリッピング奥側距離

public:
    // プロジェクション行列を返す
    DirectX::XMMATRIX GetMat() override;

    void SetFOV  (float fov);   // 視野角セット
    void SetAR   (float ar);    // アスペクト比セット
    void SetNearZ(float nearZ); // クリッピング手前側距離セット
    void SetFarZ (float farZ);  // クリッピング奥側距離セット

    ProjMat();
    ~ProjMat();
};