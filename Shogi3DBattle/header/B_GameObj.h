#pragma once

#include"I_GameObj.h"
#include<memory>

class B_GameObj : public I_GameObj
{
protected:
    std::unique_ptr<Vertices> _vertices; // 頂点集合
    std::unique_ptr<WorldMat> _worldMat; // ワールド行列
    GameObjType _gameObjType; // ゲームオブジェクトタイプ
    
public:
    void      SetVertices(Vertices* vertices) override {_vertices.reset(vertices);} // 頂点集合セット
    Vertices* GetVertices()                   override {return _vertices.get();}    // 頂点集合を返す

    void      SetWorldMat(WorldMat* worldMat) override {_worldMat.reset(worldMat);} // ワールド行列セット
    WorldMat* GetWorldMat()                   override {return _worldMat.get();}    // ワールド行列セット 

    void        SetGameObjType(GameObjType type) override {_gameObjType = type;} // ゲームオブジェクトタイプセット
    GameObjType GetGameObjType()                 override {return _gameObjType;} // ゲームオブジェクトタイプを返す
};