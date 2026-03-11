#include"CBuffMap.h"

// コンスタントバッファをマップ
HRESULT CBuffMap::MapCBuff(ID3D12Resource* _cBuff)
{
    return _cBuff->Map(0, nullptr, (void**)&_cBuffMap);
}

//void CBuffMap::RotationY(float pi)
//{
//    DirectX::XMMATRIX mat = DirectX::XMMatrixIdentity();
//
//    mat *= DirectX::XMMatrixRotationX(pi);
//
//    DirectX::XMFLOAT3 eye   (0,  0, -5);
//    DirectX::XMFLOAT3 target(0,  0,  0);
//    DirectX::XMFLOAT3 up    (0,  1,  0);
//    mat *= DirectX::XMMatrixLookAtLH(
//        DirectX::XMLoadFloat3(&eye),
//        DirectX::XMLoadFloat3(&target),
//        DirectX::XMLoadFloat3(&up));
//
//    mat *= DirectX::XMMatrixPerspectiveFovLH(
//            DirectX::XM_PIDIV2, // 画角
//            16.0f /9.0f,   // アスペクト比
//            1.0f,   // 手前側の画面までの距離
//            10.0f); //   奥側の画面までの距離
//
//    *_cBuffMap = mat;
//}

// 変換行列を書き込む
void CBuffMap::WriteMat(DirectX::XMMATRIX mat)
{
    DirectX::XMFLOAT3 eye   (0,  0, -5);
    DirectX::XMFLOAT3 target(0,  0,  0);
    DirectX::XMFLOAT3 up    (0,  1,  0);
    mat *= DirectX::XMMatrixLookAtLH(
        DirectX::XMLoadFloat3(&eye),
        DirectX::XMLoadFloat3(&target),
        DirectX::XMLoadFloat3(&up));

    mat *= DirectX::XMMatrixPerspectiveFovLH(
            DirectX::XM_PIDIV2, // 画角
            16.0f /9.0f,   // アスペクト比
            1.0f,   // 手前側の画面までの距離
            10.0f); //   奥側の画面までの距離

    *_cBuffMap = mat;
}

CBuffMap::CBuffMap(){}
CBuffMap::~CBuffMap(){}