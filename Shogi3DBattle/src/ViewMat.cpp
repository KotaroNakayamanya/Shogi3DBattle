#include"ViewMat.h"
#include<cmath>

DirectX::XMMATRIX ViewMat::GetViewMat()
{
    
    return DirectX::XMMatrixLookAtLH(
        DirectX::XMLoadFloat3(_eye.get()),
        DirectX::XMLoadFloat3(_target.get()),
        DirectX::XMLoadFloat3(_up.get()));
}


// 水平方向に視点を回す
void ViewMat::RotationH(float x)
{
    auto eyeVec      = GetEyeVec(); // 視線対象を原点としたeyeのベクトル
    auto rotationHMat = DirectX::XMMatrixRotationZ(-x); // Z軸を中心に回らせる行列

    auto newEyeVec = GetFloat3MulMat(eyeVec, rotationHMat); // ベクトルをZ軸中心に回す
    auto newEye    = GetFloat3AddFloat3(newEyeVec, *_target.get()); // ベクトルを座標に戻す

    CheckUpdateEye(newEye);
}
 
// 垂直方向に視点を回す
void ViewMat::RotationV(float y)
{
    auto eyeVec = GetEyeVec(); // 視線対象を原点としたeyeのベクトル
    auto rotationVMat =  DirectX::XMMatrixRotationX(-y); // X軸を中心に回らせる行列



    // x軸を中心とした回転で垂直方向に回転するため、準備としてeyeVecをx=0とすることのできる回転行列を作る

    auto eyeVec_z0 = eyeVec; // まず、eyeベクトルのz要素を0にしたベクトルを作る
    eyeVec_z0.z    = 0;

    auto normEyeVec_z0 = GetNormFloat3(eyeVec_z0); // 正規化したeyeベクトルを取得する

    float cos = -normEyeVec_z0.y;

    float pi = normEyeVec_z0.x > 0 ?
        -std::acos(cos) : std::acos(cos); // zのマイナス側から見たとき、反時計回りを正として考える

    auto rotationHMat = DirectX::XMMatrixRotationZ(pi); //水平方向回転行列 左手座標のためマイナス
    auto rotationHReverseMat = DirectX::XMMatrixRotationZ(-pi); //水平方向回転行列（戻し用）
        

    
    // normEyeVec_z0は正規化されていることから、normEyeVec_z0.yは、y軸単位ベクトル(0,1,0)との内積の結果になる
    // eyeのyはマイナスであることをデフォルトにしたい、
    // この際、
    // ①正規化されたもの同士での内積はcosθと同値であるため、【-normEyeVec_z0.y = cosθ】
    // ②normEyeVec_z0.z = 0, y軸単位ベクトルのz = 0 であることから、【2つのベクトルの角度はx及びyの平面で作られる】
    // 
    
    auto newEyeVec = eyeVec;
    newEyeVec = GetFloat3MulMat(newEyeVec, rotationHMat);       // ベクトルを水平方向に回転する
    newEyeVec = GetFloat3MulMat(newEyeVec, rotationVMat);       // ベクトルをX軸中心に回す
    newEyeVec = GetFloat3MulMat(newEyeVec, rotationHReverseMat);// ベクトルの水平方向回転を戻す
    auto newEye = GetFloat3AddFloat3(newEyeVec, *_target.get()); // ベクトルを座標に戻す

    CheckUpdateEye(newEye);
}

// eye - target でベクトルを取得
DirectX::XMFLOAT3 ViewMat::GetEyeVec()
{
    return GetFloat3SubFloat3(*_eye.get(), *_target.get());
}

// 視点アップデートチェック
void ViewMat::CheckUpdateEye(DirectX::XMFLOAT3 eye)
{
    if(eye.z > -4.8f && eye.z < -1.0f)
        *_eye.get() = eye;
}

// 正規化
DirectX::XMFLOAT3 ViewMat::GetNormFloat3(
    DirectX::XMFLOAT3 f)
{
    auto v = DirectX::XMLoadFloat3(&f);
    auto newV = DirectX::XMVector3Normalize(v);

    DirectX::XMFLOAT3 newF = GetFloat3FromVec(newV);

    return newF;
}

// XMFLOAT3 + XMFLOAT3
DirectX::XMFLOAT3 ViewMat::GetFloat3AddFloat3(
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
DirectX::XMFLOAT3 ViewMat::GetFloat3SubFloat3(
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
DirectX::XMFLOAT3 ViewMat::GetFloat3MulMat(
    DirectX::XMFLOAT3 f,
    DirectX::XMMATRIX mat)
{
    auto v = DirectX::XMLoadFloat3(&f);
    auto newV = DirectX::XMVector3Transform(v, mat);

    DirectX::XMFLOAT3 newF = GetFloat3FromVec(newV);

    return newF;
}

// XMVECTOR → XMFLOAT3
DirectX::XMFLOAT3 ViewMat::GetFloat3FromVec(
    DirectX::XMVECTOR v)
{
    DirectX::XMFLOAT3 f;
    DirectX::XMStoreFloat3(&f, v);

    return f;
}


ViewMat::ViewMat()
{
    _eye    = std::make_unique<DirectX::XMFLOAT3>(0.0f, -3.0f, -4.0f);
    _target = std::make_unique<DirectX::XMFLOAT3>(0.0f,  0.0f, -2.0f);
    _up     = std::make_unique<DirectX::XMFLOAT3>(0.0f,  0.0f, -1.0f);
}

ViewMat::~ViewMat(){}