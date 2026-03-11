#pragma once

#include<DirectXMath.h>

class VertexStruct
{
public:
    typedef struct Vertex
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT2 uv;
    }Vertex;

    VertexStruct(){}
    ~VertexStruct(){}
};
