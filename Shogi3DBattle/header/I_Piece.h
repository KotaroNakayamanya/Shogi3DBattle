#pragma once

#include<DirectXMath.h>
#include<VertStruct.h>
#include"WorldMat.h"
#include"Vertices.h"

class I_Piece
{
public:
    virtual void Move(DirectX::XMFLOAT3 vec) = 0; // 移動

    virtual Vertices* GetVertices() = 0; // 頂点集合を返す
    virtual void      SetWorldMat(WorldMat* mat) = 0; // ワールド行列セット
    virtual WorldMat* GetWorldMat() = 0; // ワールド行列を返す

    virtual ~I_Piece() = default;
};