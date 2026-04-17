#include"Camera.h"
#include<cmath>
#include"VecCalc.h"
#include<vector>

void Camera::SetCameraPos(DirectX::XMFLOAT3 pos)  {_viewMat->SetEye(pos);}       // カメラ位置セット
DirectX::XMFLOAT3 Camera::GetCameraPos()          {return _viewMat->GetEye();}   // カメラ位置を返す
void Camera::SetFocusPos(DirectX::XMFLOAT3 pos)   {_viewMat->SetFocus(pos);}     // フォーカス位置セット
DirectX::XMFLOAT3 Camera::GetFocusPos()           {return _viewMat->GetFocus();} // カメラ位置を返す
void Camera::SetCameraUpVec(DirectX::XMFLOAT3 vec){_viewMat->SetUp(vec);}        // カメラ上側ベクトルセット
DirectX::XMFLOAT3 Camera::GetCameraUpVec()        {return _viewMat->GetUp();}    // カメラ上側ベクトルを返す

// カメラ移動
void Camera::MoveCameraPos(DirectX::XMFLOAT3 vec)
{
    auto cameraPos = _viewMat->GetEye();
    auto newCameraPos = VecCalc::GetFloat3AddFloat3(cameraPos, vec);
    SetCameraPos(newCameraPos);
}

// フォーカス位置移動
void  Camera::MoveFocusPos(DirectX::XMFLOAT3 vec)
{
    auto focusPos = _viewMat->GetFocus();
    auto newFocusPos = VecCalc::GetFloat3AddFloat3(focusPos, vec);
    SetFocusPos(newFocusPos);
}

// 水平方向に視点を回す
void Camera::RotationH(float x)
{
    auto originPos = GetFocusPos();                                          // 注視点の座標を原点とする
    auto cameraVec = VecCalc::GetFloat3SubFloat3(GetCameraPos(), originPos); // 原点座標からカメラ座標へのベクトル

    auto rotationHMat = DirectX::XMMatrixRotationZ(-x); // Z軸（垂直）を中心に回らせる行列

    auto newCameraVec = VecCalc::GetFloat3MulMat(cameraVec, rotationHMat);    // Z軸を中心に回転した新しいベクトルを取得
    auto newCameraPos = VecCalc::GetFloat3AddFloat3(originPos, newCameraVec); // 原点からベクトルを足して新しい座標を取得

    //CheckUpdateEye(newEye); // 視点位置チェック
    SetCameraPos(newCameraPos);
    
}

// 垂直方向に視点を回す
void Camera::RotationV(float y)
{
    auto originPos = GetFocusPos();                                          // 注視点の座標を原点とする
    auto cameraVec = VecCalc::GetFloat3SubFloat3(GetCameraPos(), originPos); // 原点座標からカメラ座標のベクトル

    auto rotationVMat =  DirectX::XMMatrixRotationX(-y); // X軸（水平）を中心に回らせる行列

    // ベクトルを(0, -1, 0)に変換してからx軸を中心に回転する準備をする
    // z（垂直）を0にしたeyeベクトルを作成し、正規化する
    auto cameraVec_z0 = cameraVec;
    cameraVec_z0.z    = 0;
    auto normCameraVec_z0 = VecCalc::GetNormFloat(cameraVec_z0);
    
    // ① 正規化した者同士の内積はcosθ
    // ② normCameraVec_z0と(0, -1, 0)の内積の値は -normCameraVec_z0.y
    // ①②よりcosθ = -normCameraVec_z0.yであり、両方ともzが0であるため、θはxy平面（水平）で作られる角度である
    float cos = -normCameraVec_z0.y;

    // θを計算する ベクトルがx > 0であれば時計回り、x < 0であれば反時計回りに回転させるためにθを取得
    float theta = normCameraVec_z0.x > 0 ?
        -std::acos(cos) : std::acos(cos); 

    auto rotationHMat = DirectX::XMMatrixRotationZ(theta); //水平方向回転行列
    auto rotationHReverseMat = DirectX::XMMatrixRotationZ(-theta); //水平方向回転行列（戻し用）
    
    auto newCameraVec = cameraVec;
    newCameraVec = VecCalc::GetFloat3MulMat(newCameraVec, rotationHMat);        // ベクトルを水平方向に回転し、(0, -1, 0)に変換
    newCameraVec = VecCalc::GetFloat3MulMat(newCameraVec, rotationVMat);        // ベクトルをX軸を中心に回転
    newCameraVec = VecCalc::GetFloat3MulMat(newCameraVec, rotationHReverseMat); // ベクトルの水平方向の回転を戻す
    auto newCameraPos = VecCalc::GetFloat3AddFloat3(originPos, newCameraVec);   // 原点からベクトルを足して新しい座標を取得

    //CheckUpdateEye(newEye); // 視点位置チェック
    _viewMat->SetEye(newCameraPos);
}


// 正規化された視線ベクトルを返す
DirectX::XMFLOAT3 Camera::GetNormLookVec()
{
    auto lookVec = VecCalc::GetFloat3SubFloat3(_viewMat->GetFocus(), _viewMat->GetEye());
    return VecCalc::GetNormFloat(lookVec);
}

 






void Camera::SetViewMat(ViewMat* viewMat){_viewMat.reset(viewMat);} // ビュー行列セット
ViewMat* Camera::GetViewMat()            {return _viewMat.get();}   // ビュー行列を返す
void Camera::SetProjMat(I_ProjMat* projMat)    {_projMat.reset(projMat);} // プロジェクション行列セット
I_ProjMat* Camera::GetProjMat()                {return _projMat.get();}   // プロジェクション行列を返す

// バッファに書き込み
void Camera::WriteToBuff(ID3D12Resource* buff)
{
    DirectX::XMMATRIX* buffMap;

    HRESULT result;
    result = buff->Map(0, nullptr, (void**)&buffMap);
    assert(SUCCEEDED(result));

    buffMap += _startDataIdx;

    std::vector<DirectX::XMMATRIX> datas = {_viewMat->GetMat() * _projMat->GetMat()};

    std::copy(datas.begin(), datas.end(), buffMap);

    buff->Unmap(0, nullptr);
}