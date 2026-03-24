#include"VecCalc.h"


// ê≥ãKâª
DirectX::XMFLOAT3 VecCalc::GetNormFloat(
    DirectX::XMFLOAT3 f)
{
    auto v = DirectX::XMLoadFloat3(&f);
    auto newV = DirectX::XMVector3Normalize(v);

    DirectX::XMFLOAT3 newF = GetFloat3FromVec(newV);

    return newF;
}
DirectX::XMFLOAT2 VecCalc::GetNormFloat(
    DirectX::XMFLOAT2 f)
{
    auto v = DirectX::XMLoadFloat2(&f);
    auto newV = DirectX::XMVector2Normalize(v);

    DirectX::XMFLOAT2 newF = GetFloat2FromVec(newV);

    return newF;
}

// XMFLOAT3 + XMFLOAT3
DirectX::XMFLOAT3 VecCalc::GetFloat3AddFloat3(
    DirectX::XMFLOAT3 f1,
    DirectX::XMFLOAT3 f2)
{
    auto v1 = DirectX::XMLoadFloat3(&f1);
    auto v2 = DirectX::XMLoadFloat3(&f2);
    auto newV = DirectX::XMVectorAdd(v1, v2);

    DirectX::XMFLOAT3 newF = GetFloat3FromVec(newV);

    return  newF;
}

// XMFLOAT3 - XMFLOAT3
DirectX::XMFLOAT3 VecCalc::GetFloat3SubFloat3(
    DirectX::XMFLOAT3 f1,
    DirectX::XMFLOAT3 f2)
{
    auto v1 = DirectX::XMLoadFloat3(&f1);
    auto v2 = DirectX::XMLoadFloat3(&f2);
    auto newV = DirectX::XMVectorSubtract(v1, v2);

    DirectX::XMFLOAT3 newF = GetFloat3FromVec(newV);

    return  newF;
}

// XMFLOAT3 * XMMATRIX
DirectX::XMFLOAT3 VecCalc::GetFloat3MulMat(
    DirectX::XMFLOAT3 f,
    DirectX::XMMATRIX mat)
{
    auto v = DirectX::XMLoadFloat3(&f);
    auto newV = DirectX::XMVector3Transform(v, mat);

    DirectX::XMFLOAT3 newF = GetFloat3FromVec(newV);

    return newF;
}

// XMVECTOR Å® XMFLOAT3
DirectX::XMFLOAT3 VecCalc::GetFloat3FromVec(
    DirectX::XMVECTOR v)
{
    DirectX::XMFLOAT3 f;
    DirectX::XMStoreFloat3(&f, v);

    return f;
}

// XMVECTOR Å® XMFLOAT2
DirectX::XMFLOAT2 VecCalc::GetFloat2FromVec(
    DirectX::XMVECTOR v)
{
    DirectX::XMFLOAT2 f;
    DirectX::XMStoreFloat2(&f, v);

    return f;
}
