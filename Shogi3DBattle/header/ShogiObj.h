#pragma once

#include<d3d12.h>
#include<vector>
#include<DirectXMath.h>

class ShogiObj
{
public:
    // 頂点の内訳
    typedef struct Vert
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT2 uv;
        UINT idx;
    }Vert;

    // 将棋オブジェクトタイプ
    enum ShogiObjType
    {
        KING,
        ROOK,
        BISHOP,
        GOLD,
        SILVER,
        KNIGHT,
        LANCE,
        PAWN,
        BOARD
    };
    /*enum ShogiObjType
    {
        KING_1,
        KING_2,
        ROOK_1,
        ROOK_2,
        BISHOP_1,
        BISHOP_2,
        GOLD_1,
        GOLD_2,
        GOLD_3,
        GOLD_4,
        SILVER_1,
        SILVER_2,
        SILVER_3,
        SILVER_4,
        KNIGHT_1,
        KNIGHT_2,
        KNIGHT_3,
        KNIGHT_4,
        LANCE_1,
        LANCE_2,
        LANCE_3,
        LANCE_4,
        PAWN_1,
        PAWN_2,
        PAWN_3,
        PAWN_4,
        PAWN_5,
        PAWN_6,
        PAWN_7,
        PAWN_8,
        PAWN_9,
        PAWN_10,
        PAWN_11,
        PAWN_12,
        PAWN_13,
        PAWN_14,
        PAWN_15,
        PAWN_16,
        PAWN_17,
        PAWN_18,
        BOARD
    };*/

protected:
    UINT _id; // 将棋オブジェクトID
    std::vector<Vert> _vertices; // 頂点集合
    std::vector<unsigned short>   _indices;  // 頂点インデックス
    DirectX::XMMATRIX             _worldMat = DirectX::XMMatrixIdentity(); // ワールド行列
    D3D12_GPU_VIRTUAL_ADDRESS     _vertAddress; // 頂点アドレス
    D3D12_GPU_VIRTUAL_ADDRESS     _idxAddress;  // インデックスアドレス
    

public:
    void SetVertices(std::vector<Vert> vertices);
    void SetIndices(std::vector<unsigned short> indices);

    std::vector<Vert> GetVertices(); // 頂点集合を返す
    UINT GetVertexByteSize();   // 頂点１つ分のバイトサイズを返す
    UINT GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    std::vector<unsigned short> GetIndices(); // 頂点インデックスを返す
    UINT GetIdxNum();      // 頂点インデックスの個数を返す
    UINT GetIndexByteSize();   // 頂点インデックス1つ分のバイトサイズを返す
    UINT GetIndicesByteSize(); // 頂点インデックス全体のバイトサイズを返す

    void SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address); // 頂点アドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetVertAddress();             // 頂点アドレスを返す
    void SetIdxAddress (D3D12_GPU_VIRTUAL_ADDRESS address); // インデックスアドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetIdxAddress();              // インデックスアドレスを返す
    void SetId(UINT id); // 将棋オブジェクトIDセット
    UINT GetId();        // 将棋オブジェクトIDを返す

    DirectX::XMMATRIX GetWorldMat(); // ワールド行列を返す

    ShogiObj();
    ~ShogiObj();
};