#pragma once

#include"Vertices.h"
#include"WorldMat.h"
#include"GameObjType.h"

class I_GameObj
{
public:
    virtual void      SetVertices(Vertices* vertices) = 0; // 頂点集合セット
    virtual Vertices* GetVertices()                   = 0; // 頂点集合を返す

    virtual void      SetWorldMat(WorldMat* worldMat) = 0; // ワールド行列セット
    virtual WorldMat* GetWorldMat()                   = 0;// ワールド行列セット 

    virtual void        SetGameObjType(GameObjType type) = 0; // ゲームオブジェクトタイプセット
    virtual GameObjType GetGameObjType()                 = 0;// ゲームオブジェクトタイプを返す

    virtual ~I_GameObj() = default;
};