#pragma once

#include"IMat.h"
#include<memory>

class IProjMat : public IMat
{
//private:
    //float _fov;   // 視野角
    //float _ar;    // アスペクト比
    //float _nearZ; // クリッピング手前側距離
    //float _farZ;  // クリッピング奥側距離
protected:
    float _nearZ; // クリッピング手前側距離
    float _farZ;  // クリッピング奥側距離

public:
    // プロジェクション行列を返す
    virtual DirectX::XMMATRIX GetMat() = 0;

    //void SetFOV  (float fov);   // 視野角セット
    //void SetAR   (float ar);    // アスペクト比セット
    void SetNearZ(float nearZ){_nearZ = nearZ;} // クリッピング手前側距離セット
    void SetFarZ (float farZ) {_farZ  = farZ; } // クリッピング奥側距離セット

    IProjMat() = default;
    ~IProjMat(){};
};