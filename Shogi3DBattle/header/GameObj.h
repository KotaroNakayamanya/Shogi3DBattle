#pragma once

#include<Vertices.h>

class GameObj
{
public:
    struct Vert
    {
        DirectX::XMFLOAT3 pos;    // 頂点座標
        DirectX::XMFLOAT3 normal; // 法線
        DirectX::XMFLOAT2 uv;     // uv座標
        UCHAR objId; // 将棋オブジェクトID
        UCHAR texId; // テクスチャID
    };
private:
    std::vector<Vert> _vertices;            // 頂点集合
    std::vector<unsigned short>  _indices;  // インデックス集合
    
public:
    void                         SetVertices(std::vector<Vert> vertices)         {_vertices = vertices;} // 頂点集合セット
    std::vector<Vert>            GetVertices()                                   {return _vertices;}     // 頂点集合を返す
    void                         SetIndices (std::vector<unsigned short> indices){_indices = indices;}   // インデックス集合セット
    std::vector<unsigned short>  GetIndices ()                                   {return _indices;}      // インデックス集合を返す

    GameObj () = default;
    ~GameObj() = default;
};