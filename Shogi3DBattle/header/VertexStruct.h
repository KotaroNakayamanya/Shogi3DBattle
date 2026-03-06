#pragma once

#include<DirectXMath.h>

class VertexStruct
{
public:
    typedef struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT2 uv;
    }Vertex;
};
