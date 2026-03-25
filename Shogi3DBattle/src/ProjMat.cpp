#include"ProjMat.h"

// プロジェクション行列を返す
DirectX::XMMATRIX ProjMat::GetMat()
{
    return DirectX::XMMatrixPerspectiveFovLH(_fov, _ar, _nearZ, _farZ);
}

void ProjMat::SetFOV(float fov){_fov = fov;}         // 視野角セット
void ProjMat::SetAR(float ar){_ar = ar;}             // アスペクト比セット
void ProjMat::SetNearZ(float nearZ){_nearZ = nearZ;} // クリッピング手前側距離セット
void ProjMat::SetFarZ(float farZ){_farZ = farZ;}     // クリッピング奥側距離セット

ProjMat::ProjMat(){}
ProjMat::~ProjMat(){}