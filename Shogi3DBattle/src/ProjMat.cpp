#include"ProjMat.h"

DirectX::XMMATRIX ProjMat::GetProjMat()
{
    return *_projMat.get();
}

ProjMat::ProjMat()
{
    _projMat = std::make_unique<DirectX::XMMATRIX>();

    *_projMat = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XM_PIDIV2, // 画角90度
        16.0f /9.0f,        // アスペクト比16:9
        1.0f,               // 手前側の画面までの距離
        200.0f);             //   奥側の画面までの距離
}

ProjMat::~ProjMat(){}