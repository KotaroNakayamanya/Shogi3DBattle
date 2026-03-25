#include"ViewMat.h"
#include<cmath>

// ビュー行列を返す
DirectX::XMMATRIX ViewMat::GetMat()
{
    return DirectX::XMMatrixLookAtLH(
        DirectX::XMLoadFloat3(&_eye),
        DirectX::XMLoadFloat3(&_focus),
        DirectX::XMLoadFloat3(&_up));
}




// 水平方向に視点を回す
void ViewMat::RotationH(float x)
{
    auto eyeVec = VecCalc::GetFloat3SubFloat3(_eye, _focus); // 注視点位置を原点とするベクトル

    auto rotationHMat = DirectX::XMMatrixRotationZ(-x); // Z軸を中心に回らせる行列

    auto newEyeVec = VecCalc::GetFloat3MulMat(eyeVec, rotationHMat); // ベクトルをZ軸中心に回す
    auto newEye    = VecCalc::GetFloat3AddFloat3(newEyeVec, _focus); // ベクトルを座標に戻す

    CheckUpdateEye(newEye); // 視点位置チェック
}



 
// 垂直方向に視点を回す
void ViewMat::RotationV(float y)
{
    auto eyeVec = VecCalc::GetFloat3SubFloat3(_eye, _focus); // 視線対象を原点としたeyeのベクトル

    auto rotationVMat =  DirectX::XMMatrixRotationX(-y); // X軸を中心に回らせる行列

    // ベクトルを(0, -1, 0)に変換してからx軸を中心に回転する準備をする
    // z方向を0にしたeyeベクトルを作成し、正規化する
    auto eyeVec_z0 = eyeVec;
    eyeVec_z0.z    = 0;
    auto normEyeVec_z0 = VecCalc::GetNormFloat(eyeVec_z0);
    
    // (x, y, z)と(0, -1, 0)の内積の値は-y
    // 正規化した者同士の内積はcosθ　     よってcosθ=-y
    float cos = -normEyeVec_z0.y;

    // θを計算する 左手座標系により、z軸のマイナス側（上）から見たとき、反時計回りへの回転が正である
    float pi = normEyeVec_z0.x > 0 ?
        -std::acos(cos) : std::acos(cos); 

    auto rotationHMat = DirectX::XMMatrixRotationZ(pi); //水平方向回転行列
    auto rotationHReverseMat = DirectX::XMMatrixRotationZ(-pi); //水平方向回転行列（戻し用）
    
    auto newEyeVec = eyeVec;
    newEyeVec = VecCalc::GetFloat3MulMat(newEyeVec, rotationHMat);       // ベクトルを水平方向に回転し、ベクトルを(0, -1, 0)に変換
    newEyeVec = VecCalc::GetFloat3MulMat(newEyeVec, rotationVMat);       // ベクトルをX軸中心に回す
    newEyeVec = VecCalc::GetFloat3MulMat(newEyeVec, rotationHReverseMat);// ベクトルの水平方向回転を戻す
    auto newEye = VecCalc::GetFloat3AddFloat3(newEyeVec, _focus); // ベクトルを座標に戻す

    CheckUpdateEye(newEye); // 視点位置チェック
}




// 視点位置移動
void ViewMat::MoveEye(float x, float y, float z)
{
    _eye.x += x;
    _eye.y += y;
    _eye.z += z;
}

// 注視点位置移動
void ViewMat::MoveFocus(float x, float y, float z)
{
    _focus.x += x;
    _focus.y += y;
    _focus.z += z;
}

// 視点アップデートチェック
void ViewMat::CheckUpdateEye(DirectX::XMFLOAT3 eye)
{
    //if(eye.z > -4.8f && eye.z < -1.0f)
        _eye = eye;
}

void ViewMat::SetEye  (float x, float y, float z)  {_eye   = {x, y, z};}     // 視点位置セット
void ViewMat::SetFocus(float x, float y, float z)  {_focus = {x, y, z};} // 注視点位置セット
void ViewMat::SetUp   (float x, float y, float z)  {_up    = {x, y, z};}       // カメラ上側セット

ViewMat::ViewMat(){}
ViewMat::~ViewMat(){}