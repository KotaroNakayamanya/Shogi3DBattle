#pragma once

#include<DirectXMath.h>
#include<memory>
#include<vector>
#include<NaturalBufferedData.h>
#include"Vertices.h"
#include"WorldMat.h"
#include"GameObjType.h"

class GameObj
{
protected:
    std::unique_ptr<Vertices> _vertices; // 頂点集合
    std::unique_ptr<WorldMat> _worldMat; // ワールド行列
    GameObjType _gameObjType; // ゲームオブジェクトタイプ
    
public:
    void      SetVertices(Vertices* vertices){_vertices.reset(vertices);} // 頂点集合セット
    Vertices* GetVertices()                  {return _vertices.get();}    // 頂点集合を返す
    void      SetWorldMat(WorldMat* worldMat){_worldMat.reset(worldMat);} // ワールド行列セット
    WorldMat* GetWorldMat()                  {return _worldMat.get();}    // ワールド行列セット 

    void        SetGameObjType(GameObjType type){_gameObjType = type;} // ゲームオブジェクトタイプセット
    GameObjType GetGameObjType()                {return _gameObjType;} // ゲームオブジェクトタイプを返す

    ~GameObj() = default;
};