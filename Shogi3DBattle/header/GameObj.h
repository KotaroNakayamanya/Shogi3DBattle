#pragma once

#include<DirectXMath.h>
#include<memory>
#include<vector>
#include<NaturalBufferedData.h>
#include"WorldMat.h"

class GameObj
{
public:
    struct Vert // 頂点情報
    {
        DirectX::XMFLOAT3 pos;    // 頂点座標
        DirectX::XMFLOAT3 normal; // 法線
        DirectX::XMFLOAT2 uv;     // uv座標
        unsigned char objId;       // 将棋オブジェクトID　 (ワールド座標区別に使用)
        unsigned char basicTexId;  // 基本テクスチャID　　（木材等）
        unsigned char designTexId; // デザインテクスチャID（文字、黒線等）
    };

protected:
    std::unique_ptr<NaturalBufferedData<Vert>> _vertices; // 頂点集合
    std::unique_ptr<WorldMat>                  _worldMat; // ワールド行列
    
public:
    void                       SetVertices(NaturalBufferedData<Vert> vertices){_vertices.reset(new NaturalBufferedData<Vert>(vertices));} // 頂点集合セット
    NaturalBufferedData<Vert>* GetVertices()                                  {return _vertices.get();}                                   // 頂点集合を返す
    void                       SetWorldMat(WorldMat worldMat)                 {_worldMat.reset(new WorldMat(worldMat));}                  // ワールド行列セット
    WorldMat*                  GetWorldMat()                                  {return _worldMat.get();}                                   // ワールド行列セット

    ~GameObj() = default;
};