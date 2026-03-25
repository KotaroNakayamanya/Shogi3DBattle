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
        DirectX::XMFLOAT3 pos;    // 頂点座標
        DirectX::XMFLOAT3 normal; // 法線
        DirectX::XMFLOAT2 uv;     // uv座標
        UCHAR objId; // 将棋オブジェクトID
        UCHAR texId; // テクスチャID
    }Vert;

    // 将棋オブジェクトタイプ
    enum ShogiObjType
    {   
        BOARD,  // 将棋盤
        KING,   // 王
        ROOK,   // 飛車
        BISHOP, // 角行
        GOLD,   // 金将
        SILVER, // 銀将
        KNIGHT, // 桂馬
        LANCE,  // 香車
        PAWN    // 歩
    };

protected:
    UINT _objId; // 将棋オブジェクトID
    UINT _texId; // 使用するテクスチャID
    std::vector<Vert> _vertices; // 頂点集合
    std::vector<USHORT>   _indices;  // 頂点インデックス
    DirectX::XMMATRIX             _worldMat = DirectX::XMMatrixIdentity(); // ワールド行列
    D3D12_GPU_VIRTUAL_ADDRESS     _vertAddress; // 頂点アドレス
    D3D12_GPU_VIRTUAL_ADDRESS     _idxAddress;  // インデックスアドレス
    

public:
    void SetVertices(std::vector<Vert> vertices); // 頂点集合セット
    std::vector<Vert> GetVertices();              // 頂点集合を返す
    void SetIndices(std::vector<USHORT> indices);  // インデックスセット
    std::vector<USHORT> GetIndices();              // 頂点インデックスを返す
   
    UINT GetVertexByteSize();   // 頂点１つ分のバイトサイズを返す
    UINT GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    
    //std::vector<unsigned short> GetIndices(); // 頂点インデックスを返す
    UINT GetIdxNum();      // 頂点インデックスの個数を返す
    UINT GetIndexByteSize();   // 頂点インデックス1つ分のバイトサイズを返す
    UINT GetIndicesByteSize(); // 頂点インデックス全体のバイトサイズを返す

    void SetVertAddress(D3D12_GPU_VIRTUAL_ADDRESS address); // 頂点アドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetVertAddress();             // 頂点アドレスを返す
    void SetIdxAddress (D3D12_GPU_VIRTUAL_ADDRESS address); // インデックスアドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetIdxAddress();              // インデックスアドレスを返す
    void  SetObjId(UCHAR objId); // 将棋オブジェクトIDセット
    UCHAR GetObjId();        // 将棋オブジェクトIDを返す
    void  SetTexId(UCHAR texId); // テクスチャIDセット
    UCHAR GetTexId();           // テクスチャIDを返す

    DirectX::XMMATRIX GetWorldMat(); // ワールド行列を返す

    ShogiObj();
    ~ShogiObj();
};