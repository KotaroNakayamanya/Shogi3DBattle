#pragma once

#include<DirectXMath.h>
#include<VertStruct.h>
#include"I_WorldMat.h"
#include"I_Vertices.h"

class I_Piece
{
public:
    virtual void Move(DirectX::XMFLOAT3 vec) = 0; // 移動

    virtual I_Vertices* GetVertices() = 0; // 頂点集合を返す
    virtual void      SetWorldMat(I_WorldMat* mat) = 0; // ワールド行列セット
    virtual I_WorldMat* GetWorldMat() = 0; // ワールド行列を返す

    virtual ~I_Piece() = default;
};