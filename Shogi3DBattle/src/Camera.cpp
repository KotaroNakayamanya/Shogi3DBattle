#include"Camera.h"
#include<cmath>
#include"VecCalc.h"



// 水平方向に視点を回す
void Camera::RotationH(float x)
{
    auto eye   = _viewMat->GetEye();   // 視点位置
    auto focus = _viewMat->GetFocus(); // 注視点位置

    auto eyeVec = VecCalc::GetFloat3SubFloat3(eye, focus); // 注視点位置を原点とするベクトル

    auto rotationHMat = DirectX::XMMatrixRotationZ(-x); // Z軸を中心に回らせる行列

    auto newEyeVec = VecCalc::GetFloat3MulMat(eyeVec, rotationHMat); // ベクトルをZ軸中心に回す
    auto newEye    = VecCalc::GetFloat3AddFloat3(newEyeVec, focus); // ベクトルを座標に戻す

    //CheckUpdateEye(newEye); // 視点位置チェック
    _viewMat->SetEye(newEye);
    
}

// 正規化された視線ベクトルを返す
DirectX::XMFLOAT3 Camera::GetNormLookVec()
{
    auto lookVec = VecCalc::GetFloat3SubFloat3(_viewMat->GetFocus(), _viewMat->GetEye());
    return VecCalc::GetNormFloat(lookVec);
}

 
// 垂直方向に視点を回す
void Camera::RotationV(float y)
{
    auto eye   = _viewMat->GetEye();   // 視点位置
    auto focus = _viewMat->GetFocus(); // 注視点位置

    auto eyeVec = VecCalc::GetFloat3SubFloat3(eye, focus); // 視線対象を原点としたeyeのベクトル

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
    float theta = normEyeVec_z0.x > 0 ?
        -std::acos(cos) : std::acos(cos); 

    auto rotationHMat = DirectX::XMMatrixRotationZ(theta); //水平方向回転行列
    auto rotationHReverseMat = DirectX::XMMatrixRotationZ(-theta); //水平方向回転行列（戻し用）
    
    auto newEyeVec = eyeVec;
    newEyeVec = VecCalc::GetFloat3MulMat(newEyeVec, rotationHMat);       // ベクトルを水平方向に回転し、ベクトルを(0, -1, 0)に変換
    newEyeVec = VecCalc::GetFloat3MulMat(newEyeVec, rotationVMat);       // ベクトルをX軸中心に回す
    newEyeVec = VecCalc::GetFloat3MulMat(newEyeVec, rotationHReverseMat);// ベクトルの水平方向回転を戻す
    auto newEye = VecCalc::GetFloat3AddFloat3(newEyeVec, focus); // ベクトルを座標に戻す

    //CheckUpdateEye(newEye); // 視点位置チェック
    _viewMat->SetEye(newEye);
}

// ビュープロジェクション行列を返す
DirectX::XMMATRIX Camera::GetViewProjMat()
{
    return _viewMat->GetMat() * _projMat->GetMat();
}

// カメラ移動
void Camera::MoveCameraPos(DirectX::XMFLOAT3 vec)
{
    auto eye = _viewMat->GetEye();
    auto newEye = VecCalc::GetFloat3AddFloat3(eye, vec);
    _viewMat->SetEye(newEye);
}

// フォーカス位置移動
void  Camera::MoveFocusPos(DirectX::XMFLOAT3 vec)
{
    auto focus = _viewMat->GetFocus();
    auto newFocus = VecCalc::GetFloat3AddFloat3(focus, vec);
    _viewMat->SetFocus(newFocus);
}

void Camera::SetCameraPos(DirectX::XMFLOAT3 pos)  {_viewMat->SetEye(pos);}       // カメラ位置セット
DirectX::XMFLOAT3 Camera::GetCameraPos()          {return _viewMat->GetEye();}   // カメラ位置を返す
void Camera::SetFocusPos(DirectX::XMFLOAT3 pos)   {_viewMat->SetFocus(pos);}     // フォーカス位置セット
DirectX::XMFLOAT3 Camera::GetFocusPos()           {return _viewMat->GetFocus();} // カメラ位置を返す
void Camera::SetCameraUpVec(DirectX::XMFLOAT3 vec){_viewMat->SetUp(vec);}        // カメラ上側ベクトルセット
DirectX::XMFLOAT3 Camera::GetCameraUpVec()        {return _viewMat->GetUp();}    // カメラ上側ベクトルを返す

void Camera::SetViewMat(ViewMat* viewMat){_viewMat.reset(viewMat);} // ビュー行列セット
ViewMat* Camera::GetViewMat()            {return _viewMat.get();}   // ビュー行列を返す
void Camera::SetProjMat(IMat* projMat)   {_projMat.reset(projMat);} // プロジェクション行列セット
IMat* Camera::GetProjMat()               {return _projMat.get();}   // プロジェクション行列を返す

Camera::Camera(){}
Camera::~Camera(){}