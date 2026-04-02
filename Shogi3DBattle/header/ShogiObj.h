#pragma once

#include<d3d12.h>
#include<vector>
#include<memory>
#include"Vertices.h"
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
    //std::unique_ptr<WorldMat> _worldMat; // ワールド行列
    UINT _startVertIdxInBuff; // バッファ内に書き込まれる場所のスタート位置
    //D3D12_GPU_VIRTUAL_ADDRESS _vertBuffAddress;

    UCHAR _objId; // 将棋オブジェクトID
    UCHAR _texId; // 使用するテクスチャID
    
public:
    //void      SetWorldMat(WorldMat* worldMat){_worldMat.reset(worldMat);} // ワールド行列セット
    //WorldMat* GetWorldMat(WorldMat* worldMat){return _worldMat.get();}    // ワールド行列セット

    void  SetStartVertIdxInBuff(UINT startIdx){_startVertIdxInBuff = startIdx;} // バッファ内の頂点集合スタート位置セット
    UINT  GetStartVertIdxInBuff()             {return _startVertIdxInBuff;}     // バッファ内の頂点集合スタート位置を返す
    void  SetObjId(UCHAR objId){_objId = objId;} // 将棋オブジェクトIDセット
    UCHAR GetObjId()           {return _objId;}  // 将棋オブジェクトIDを返す
    void  SetTexId(UCHAR texId){_texId = texId;} // テクスチャIDセット
    UCHAR GetTexId()           {return _texId;}  // テクスチャIDを返す

    ShogiObj         () = default;
    virtual ~ShogiObj() = default;
};