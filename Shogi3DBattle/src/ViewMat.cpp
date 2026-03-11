#include"ViewMat.h"

DirectX::XMMATRIX ViewMat::GetViewMat()
{
    
    return DirectX::XMMatrixLookAtLH(
        DirectX::XMLoadFloat3(_eye.get()),
        DirectX::XMLoadFloat3(_target.get()),
        DirectX::XMLoadFloat3(_up.get()));
}



 
// y•ûŒü‚ÉŽ‹“_‚ð‰ñ‚·
void ViewMat::RotationY(float y)
{
    auto rotationMat =  DirectX::XMMatrixRotationX(y);
    auto v = DirectX::XMLoadFloat3(_eye.get());

    auto result = DirectX::XMVector3Transform(v, rotationMat);

    DirectX::XMFLOAT3 newEye;

    DirectX::XMStoreFloat3(&newEye, result);

    if(newEye.z > -4.8f && newEye.z < 0.0f)
        *_eye.get() = newEye;
}




ViewMat::ViewMat()
{
    _eye    = std::make_unique<DirectX::XMFLOAT3>(0.0f, -3.0f, -4.0f);
    _target = std::make_unique<DirectX::XMFLOAT3>(0.0f,  0.0f, -3.0f);
    _up     = std::make_unique<DirectX::XMFLOAT3>(0.0f,  0.0f, -1.0f);
}

ViewMat::~ViewMat(){}