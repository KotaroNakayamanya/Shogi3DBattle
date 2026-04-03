#pragma once

#include<DirectXMath.h>
#include<memory>
#include<vector>
#include<NaturalBufferedData.h>
#include"WorldMat.h"

class GameObj
{
public:
    // オブジェクトタイプ
    enum GameObjType
    {   
        KING,     // 王
        ROOK,     // 飛車
        BISHOP,   // 角行
        GOLD,     // 金将
        SILVER,   // 銀将
        KNIGHT,   // 桂馬
        LANCE,    // 香車
        PAWN,     // 歩
        BOARD_55, // 5×5将棋盤
        BOARD_99, // 9×9将棋盤
        TYPE_NUM  // 将棋オブジェクト種類数（テクスチャ用意数）
    };

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
    unsigned char _objId; // 将棋オブジェクトID
    unsigned char _texId; // 使用するテクスチャID
    
public:
    void                       SetVertices(NaturalBufferedData<Vert> vertices){_vertices.reset(new NaturalBufferedData<Vert>(vertices));} // 頂点集合セット
    NaturalBufferedData<Vert>* GetVertices()                                  {return _vertices.get();}                                   // 頂点集合を返す
    void                       SetWorldMat(WorldMat worldMat)                 {_worldMat.reset(new WorldMat(worldMat));}                  // ワールド行列セット
    WorldMat*                  GetWorldMat()                                  {return _worldMat.get();}                                   // ワールド行列セット
    void  SetObjId(unsigned char objId){_objId = objId;} // 将棋オブジェクトIDセット
    unsigned char GetObjId()           {return _objId;}  // 将棋オブジェクトIDを返す
    void  SetTexId(unsigned char texId){_texId = texId;} // テクスチャIDセット
    unsigned char GetTexId()           {return _texId;}  // テクスチャIDを返す

    ~GameObj() = default;
};