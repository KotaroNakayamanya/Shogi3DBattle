#pragma once

#include<vector>
#include"VertexStruct.h"

class Piece
{
private:
    std::vector<VertexStruct::Vertex> _vertices; // 頂点集合
    std::vector<unsigned short>       _indices;  // 頂点インデックス
    DirectX::XMMATRIX                 _worldMat; // ワールド行列

protected:
    typedef struct CreateVerticesArg // 頂点集合作成用引数
    {
        float bottomWidth;  // 底面の横の長さ
        float cornerWidth;  // 角部分の横の長さ
        float height;       // 高さ
        float cornerHeight; // 角部分の高さ
        float thickness;    // 駒の厚み

    }CreateVerticesArg;

    void SetVertices(CreateVerticesArg arg); // 頂点集合作成

public:
    void MoveX(float x); // x軸方向に動くようにワールド行列を変換する
    void MoveY(float y); // y軸方向に動くようにワールド行列を変換する

    DirectX::XMMATRIX GetWorldMat(); // ワールド行列を返す
    
    std::vector<VertexStruct::Vertex> GetVerticesPtr(); // 頂点集合を返す
    unsigned int GetVertexByteSize();   // 頂点１つ分のバイトサイズを返す
    unsigned int GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    std::vector<unsigned short> GetIndicesPtr(); // 頂点インデックスを返す
    unsigned int GetIndicesNum();      // 頂点インデックスの個数を返す
    unsigned int GetIndexByteSize();   // 頂点インデックス1つ分のバイトサイズを返す
    unsigned int GetIndicesByteSize(); // 頂点インデックス全体のバイトサイズを返す

    

    Piece();
    ~Piece();
};