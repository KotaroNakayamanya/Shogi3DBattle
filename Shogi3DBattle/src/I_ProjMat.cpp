#include"I_ProjMat.h"

void  I_ProjMat::SetNearZ(float nearZ){_nearZ = nearZ;} // クリッピング手前側距離セット
float I_ProjMat::GetNearZ()           {return _nearZ;}  // クリッピング手前側距離を返す
void  I_ProjMat::SetFarZ (float farZ) {_farZ  = farZ; } // クリッピング奥側距離セット
float I_ProjMat::GetFarZ()            {return _farZ;}   // クリッピング奥側距離を返す

I_ProjMat::I_ProjMat(float nearZ, float farZ) : _nearZ(nearZ), _farZ(farZ){}