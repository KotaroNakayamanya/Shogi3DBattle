#pragma once

#include<memory>
#include"Vertices.h"
#include"I_WorldMat.h"
#include"GameObjType.h"

class B_GameObj
{
protected:
    std::unique_ptr<Vertices> _vertices;    // 頂点集合
    std::unique_ptr<I_WorldMat> _worldMat;    // ワールド行列
    GameObjType                 _gameObjType; // ゲームオブジェクトタイプ
    
public:
    void        SetVertices(Vertices* vertices){_vertices.reset(vertices);} // 頂点集合セット
    Vertices* GetVertices()                    {return _vertices.get();}    // 頂点集合を返す

    void        SetWorldMat(I_WorldMat* worldMat){_worldMat.reset(worldMat);} // ワールド行列セット
    I_WorldMat* GetWorldMat()                    {return _worldMat.get();}    // ワールド行列セット 

    void        SetGameObjType(GameObjType type) {_gameObjType = type;} // ゲームオブジェクトタイプセット
    GameObjType GetGameObjType()                 {return _gameObjType;} // ゲームオブジェクトタイプを返す
};