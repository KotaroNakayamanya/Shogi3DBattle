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
        UINT objId;
        UINT texId;
    }Vert;

    // 将棋オブジェクトタイプ
    enum ShogiObjType
    {   
        BOARD,
        PAWN,
        
        KING,
        ROOK,
        BISHOP,
        GOLD,
        SILVER,
        KNIGHT,
        LANCE,
        
    };

protected:
    UINT _id; // 将棋オブジェクトID
    UINT _texId; // 使用するテクスチャID
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
    void SetTexId(UINT texId); // テクスチャIDセット
    UINT GetTexId();           // テクスチャIDを返す

    DirectX::XMMATRIX GetWorldMat(); // ワールド行列を返す

    ShogiObj();
    ~ShogiObj();
};