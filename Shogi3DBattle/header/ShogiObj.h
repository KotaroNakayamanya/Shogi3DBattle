#pragma once

#include<d3d12.h>
#include<vector>
#include<memory>
#include"WorldMat.h"

#include"GameObj.h"

class ShogiObj : public GameObj, public WorldMat
{
public:
    // 将棋オブジェクトタイプ
    enum ShogiObjType
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

protected:
    UCHAR _objId; // 将棋オブジェクトID
    UCHAR _texId; // 使用するテクスチャID
    
public:
    void  SetObjId(UCHAR objId){_objId = objId;} // 将棋オブジェクトIDセット
    UCHAR GetObjId()           {return _objId;}  // 将棋オブジェクトIDを返す
    void  SetTexId(UCHAR texId){_texId = texId;} // テクスチャIDセット
    UCHAR GetTexId()           {return _texId;}  // テクスチャIDを返す

    virtual ~ShogiObj() = default;
};