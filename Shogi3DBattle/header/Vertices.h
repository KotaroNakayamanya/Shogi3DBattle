#pragma once

#include"BufferedData.h"
#include<DirectXMath.h>
#include<vector>

class Vertices : public BufferedData
{
public:
    typedef struct Vert
    {
        DirectX::XMFLOAT3 pos;    // 頂点座標
        DirectX::XMFLOAT3 normal; // 法線
        DirectX::XMFLOAT2 uv;     // uv座標
        UCHAR objId; // 将棋オブジェクトID
        UCHAR texId; // テクスチャID
    }Vert;

private:
    std::vector<Vert> _vertices; // 頂点集合

public:
    UINT GetVertNum();        // 頂点数を返す 
    UINT GetVertByteSize();   // 頂点１つ分のバイトサイズを返す
    UINT GetVerticesByteSize(); // 頂点集合全体のバイトサイズを返す

    void SetVertices(std::vector<Vert> vertices); // 頂点集合セット
    std::vector<Vert> GetVertices(); // 頂点集合を返す

    Vertices();
    ~Vertices();
};