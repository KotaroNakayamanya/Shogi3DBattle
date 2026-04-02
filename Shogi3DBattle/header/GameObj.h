#pragma once

#include<DirectXMath.h>
#include<memory>
#include<vector>
#include<BufferedData.h>

class GameObj
{
public:
    struct Vert // 頂点情報
    {
        DirectX::XMFLOAT3 pos;    // 頂点座標
        DirectX::XMFLOAT3 normal; // 法線
        DirectX::XMFLOAT2 uv;     // uv座標
        unsigned char objId;       // 将棋オブジェクトID　 (ワールド座標区別に使用)
        unsigned char basicTexId;  // 基本テクスチャID　　（木材等）
        unsigned char designTexId; // デザインテクスチャID（文字、黒線等）
    };

private:
    //std::vector<Vert> _vertices;            // 頂点集合
    std::unique_ptr<BufferedData<Vert>> _vertices;            // 頂点集合
    std::vector<unsigned short>  _indices;  // インデックス集合
    
public:
    //void                         SetVertices(std::vector<Vert> vertices)         {_vertices = vertices;} // 頂点集合セット
    //std::vector<Vert>            GetVertices()                                   {return _vertices;}     // 頂点集合を返す

    void                SetVertices(BufferedData<Vert> vertices){_vertices.reset(new BufferedData<Vert>(vertices));} // 頂点集合セット
    BufferedData<Vert>* GetVertices()                           {return _vertices.get();}                            // 頂点集合を返す

    void                         SetIndices (std::vector<unsigned short> indices){_indices = indices;}   // インデックス集合セット
    std::vector<unsigned short>  GetIndices ()                                   {return _indices;}      // インデックス集合を返す

    ~GameObj() = default;
};