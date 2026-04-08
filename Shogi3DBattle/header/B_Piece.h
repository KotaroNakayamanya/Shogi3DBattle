#pragma once

#include"I_Piece.h"
#include"B_GameObj.h"

class B_Piece : public I_Piece, public B_GameObj
{
public:     
    void Move(DirectX::XMFLOAT3 vec) override; // 移動

    Vertices* GetVertices() override; // 頂点集合を返す
    void      SetWorldMat(WorldMat* mat) override; // ワールド行列セット
    WorldMat* GetWorldMat()              override; // ワールド行列を返す
};