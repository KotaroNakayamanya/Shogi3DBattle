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
    auto eyeVec = GetEyeVec(); // 視線対象を原点としたeyeのベクトル
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

    // ベクトルを(0, -1, 0)に変換してからx軸を中心に回転する準備をする

    // z方向を0にしたeyeベクトルを作成
    auto eyeVec_z0 = eyeVec;
    eyeVec_z0.z    = 0;

    // xy要素のみのベクトルで正規化
    auto normEyeVec_z0 = GetNormFloat3(eyeVec_z0);

    // 正規化した者同士の内積はcosθとなる
    // (0, -1, 0)との内積の値は、yの符号を逆転したもの
    float cos = -normEyeVec_z0.y;

    // θを計算する z軸のマイナス側（上）から見たとき、反時計回りを正として考える
    float pi = normEyeVec_z0.x > 0 ?
        -std::acos(cos) : std::acos(cos); 

    auto rotationHMat = DirectX::XMMatrixRotationZ(pi); //水平方向回転行列
    auto rotationHReverseMat = DirectX::XMMatrixRotationZ(-pi); //水平方向回転行列（戻し用）
    
    auto newEyeVec = eyeVec;
    newEyeVec = GetFloat3MulMat(newEyeVec, rotationHMat);       // ベクトルを水平方向に回転する
    newEyeVec = GetFloat3MulMat(newEyeVec, rotationVMat);       // ベクトルをX軸中心に回す
    newEyeVec = GetFloat3MulMat(newEyeVec, rotationHReverseMat);// ベクトルの水平方向回転を戻す
    auto newEye = GetFloat3AddFloat3(newEyeVec, *_target.get()); // ベクトルを座標に戻す

    CheckUpdateEye(newEye);
}




// 視点移動
void ViewMat::MoveEye(float x, float y, float z)
{
    _eye->x += x;
    _eye->y += y;
    _eye->z += z;
}

// 視線対象移動
void ViewMat::MoveTarget(float x, float y, float z)
{
    _target->x += x;
    _target->y += y;
    _target->z += z;
}

// eye - target でベクトルを取得
DirectX::XMFLOAT3 ViewMat::GetEyeVec()
{
    return GetFloat3SubFloat3(*_eye.get(), *_target.get());
}

// 視点アップデートチェック
void ViewMat::CheckUpdateEye(DirectX::XMFLOAT3 eye)
{
    //if(eye.z > -4.8f && eye.z < -1.0f)
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



DirectX::XMFLOAT3* ViewMat::GetEyePtr(){return _eye.get();}
DirectX::XMFLOAT3* ViewMat::GetTargetPtr(){return _eye.get();}


ViewMat::ViewMat()
{
    _eye    = std::make_unique<DirectX::XMFLOAT3>(0.0f, -3.0f, -4.0f);
    _target = std::make_unique<DirectX::XMFLOAT3>(0.0f,  0.0f, -2.0f);
    _up     = std::make_unique<DirectX::XMFLOAT3>(0.0f,  0.0f, -1.0f);
}

ViewMat::~ViewMat(){}