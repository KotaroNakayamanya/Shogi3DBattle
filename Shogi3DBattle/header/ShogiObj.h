#pragma once

#include<d3d12.h>
#include<vector>
#include<memory>
#include"WorldMat.h"
#include"Vertices.h"

class ShogiObj
{
public:
    //// 頂点の内訳
    //typedef struct Vert
    //{
    //    DirectX::XMFLOAT3 pos;    // 頂点座標
    //    DirectX::XMFLOAT3 normal; // 法線
    //    DirectX::XMFLOAT2 uv;     // uv座標
    //    UCHAR objId; // 将棋オブジェクトID
    //    UCHAR texId; // テクスチャID
    //}Vert;

    // 将棋オブジェクトタイプ
    enum ShogiObjType
    {   
        BOARD_55,// 将棋盤
        KING,   // 王
        ROOK,   // 飛車
        BISHOP, // 角行
        GOLD,   // 金将
        SILVER, // 銀将
        KNIGHT, // 桂馬
        LANCE,  // 香車
        PAWN,    // 歩
        BOARD_99
    };

protected:
    UINT _objId; // 将棋オブジェクトID
    UINT _texId; // 使用するテクスチャID
    std::vector<Vertices::Vert> _vertices; // 頂点集合

    //DirectX::XMMATRIX             _worldMat; // ワールド行列
    std::unique_ptr<WorldMat> _worldMat; // ワールド行列
    

    D3D12_GPU_VIRTUAL_ADDRESS     _vertAddress; // 頂点アドレス
    

public:

    UINT GetVertexByteSize();   // 頂点１つ分のバイトサイズを返す
    UINT GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    void SetVertices(std::vector<Vertices::Vert> vertices); // 頂点集合セット
    std::vector<Vertices::Vert> GetVertices();              // 頂点集合を返す
    void  SetObjId(UCHAR objId); // 将棋オブジェクトIDセット
    UCHAR GetObjId();        // 将棋オブジェクトIDを返す
    void  SetTexId(UCHAR texId); // テクスチャIDセット
    UCHAR GetTexId();           // テクスチャIDを返す
    void SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address); // 頂点アドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetVertAddress();             // 頂点アドレスを返す

    void SetWorldMat( DirectX::XMMATRIX worldMat); // ワールド行列セット
    DirectX::XMMATRIX GetWorldMat();          // ワールド行列を返す

    ShogiObj();
    ~ShogiObj();
};