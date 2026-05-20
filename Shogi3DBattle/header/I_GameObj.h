#pragma once

#include<memory>
#include"Vertices.h"
#include"WorldMat.h"
#include"GameObjType.h"

class I_GameObj
{
private:
    std::unique_ptr<Vertices> _vertices;    // 頂点集合
    std::unique_ptr<WorldMat> _worldMat;    // ワールド行列
    GameObjType               _gameObjType; // ゲームオブジェクトタイプ

protected:
    void SetVertices   (std::unique_ptr<Vertices> uniquePtr); // 頂点集合セット
    
public:
    Vertices*   GetVertices();    // 頂点集合を返す
    WorldMat*   GetWorldMat();    // ワールド行列を返す 
    GameObjType GetGameObjType(); // ゲームオブジェクトタイプを返す

    I_GameObj(GameObjType gameObjType);
};