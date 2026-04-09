#pragma once

#include"I_Vertices.h"
#include"I_WorldMat.h"
#include"GameObjType.h"

class I_GameObj
{
public:
    virtual void        SetVertices(I_Vertices* vertices) = 0; // 頂点集合セット
    virtual I_Vertices* GetVertices()                     = 0; // 頂点集合を返す

    virtual void        SetWorldMat(I_WorldMat* worldMat) = 0; // ワールド行列セット
    virtual I_WorldMat* GetWorldMat()                     = 0; // ワールド行列セット 

    virtual void        SetGameObjType(GameObjType type)  = 0; // ゲームオブジェクトタイプセット
    virtual GameObjType GetGameObjType()                  = 0; // ゲームオブジェクトタイプを返す

    virtual ~I_GameObj() = default;
};