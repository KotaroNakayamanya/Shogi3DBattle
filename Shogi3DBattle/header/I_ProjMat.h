#pragma once

#include"I_Mat.h"

class I_ProjMat : public I_Mat
{
protected:
    float _nearZ; // クリッピング手前側距離
    float _farZ ; // クリッピング奥側距離

public:
    void  SetNearZ(float nearZ); // クリッピング手前側距離セット
    float GetNearZ();            // クリッピング手前側距離を返す
    void  SetFarZ (float farZ);  // クリッピング奥側距離セット
    float GetFarZ();             // クリッピング奥側距離を返す

    I_ProjMat(float nearZ = 1.0f, float farZ = 50.0f);
    virtual ~I_ProjMat() = default;
};