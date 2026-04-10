#include"PersProjMat.h"

// パースによるプロジェクション行列を返す
DirectX::XMMATRIX PersProjMat::GetMat()
{
    return DirectX::XMMatrixPerspectiveFovLH(_fov, _ar, _nearZ, _farZ);
}

void PersProjMat::SetFOV(float fov){_fov = fov;} // 視野角セット
void PersProjMat::SetAR (float ar) {_ar  = ar; } // アスペクト比セット