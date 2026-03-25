#pragma once

#include<d3d12.h>
#include<vector>
#include<memory>
#include"WorldMat.h"
#include"Vertices.h"

class ShogiObj : public Vertices, public WorldMat
{
public:
    // 将棋オブジェクトタイプ
    enum ShogiObjType
    {   
        KING,   // 王
        ROOK,   // 飛車
        BISHOP, // 角行
        GOLD,   // 金将
        SILVER, // 銀将
        KNIGHT, // 桂馬
        LANCE,  // 香車
        PAWN,    // 歩
        BOARD_55,// 5×5将棋盤
        BOARD_99 // 9×9将棋盤
    };

protected:
    UINT _objId; // 将棋オブジェクトID
    UINT _texId; // 使用するテクスチャID
    
public:
    void  SetObjId(UCHAR objId); // 将棋オブジェクトIDセット
    UCHAR GetObjId();        // 将棋オブジェクトIDを返す
    void  SetTexId(UCHAR texId); // テクスチャIDセット
    UCHAR GetTexId();           // テクスチャIDを返す

    ShogiObj();
    ~ShogiObj();
};