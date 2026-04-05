#pragma once

#include<DirectXMath.h>

struct Vert
{
    DirectX::XMFLOAT3 pos;    // 頂点座標
    DirectX::XMFLOAT3 normal; // 法線
    DirectX::XMFLOAT2 uv;     // uv座標
    unsigned char gameObjId;       // ゲームオブジェクトID　 (ワールド座標区別に使用)
    unsigned char basicTexId;      // 基本テクスチャID　　（木材等）
    unsigned char mulDesignTexId;  // 乗算デザインテクスチャID（文字、黒線等）
};