#pragma once

#include"I_Mat.h"

class I_ProjMat : public I_Mat
{
protected:
    float _nearZ; // クリッピング手前側距離
    float _farZ ; // クリッピング奥側距離

public:
    void  SetNearZ(float nearZ){_nearZ = nearZ;} // クリッピング手前側距離セット
    float GetNearZ()           {return _nearZ;}  // クリッピング手前側距離を返す
    void  SetFarZ (float farZ) {_farZ  = farZ; } // クリッピング奥側距離セット
    float GetFarZ()            {return _farZ;}   // クリッピング奥側距離を返す

    virtual ~I_ProjMat() = default;
};