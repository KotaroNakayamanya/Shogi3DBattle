#pragma once

#include"I_Board.h"
#include<memory>

class B_GameObj : public I_Board
{
protected:
    std::unique_ptr<I_Vertices> _vertices; // 頂点集合
    std::unique_ptr<I_WorldMat> _worldMat; // ワールド行列
    GameObjType _gameObjType; // ゲームオブジェクトタイプ
    
public:
    void      SetVertices(I_Vertices* vertices) override {_vertices.reset(vertices);} // 頂点集合セット
    I_Vertices* GetVertices()                   override {return _vertices.get();}    // 頂点集合を返す

    void      SetWorldMat(I_WorldMat* worldMat) override {_worldMat.reset(worldMat);} // ワールド行列セット
    I_WorldMat* GetWorldMat()                   override {return _worldMat.get();}    // ワールド行列セット 

    void        SetGameObjType(GameObjType type) override {_gameObjType = type;} // ゲームオブジェクトタイプセット
    GameObjType GetGameObjType()                 override {return _gameObjType;} // ゲームオブジェクトタイプを返す
};