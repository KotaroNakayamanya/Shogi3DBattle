#pragma once

#include<DirectXMath.h>
#include<vector>

#include"VertexStruct.h"

class Object
{
private:
    

    //std::vector<DirectX::XMFLOAT3> _vertices =
    //{
    //    {-1.0f, -1.0f, 0.0f},
    //    {-1.0f,  1.0f, 0.0f},
    //    { 1.0f, -1.0f, 0.0f},
    //    { 0.9f,  0.9f, 0.0f}
    //};

    std::vector<VertexStruct::Vertex> _vertices =
    {
        {{-0.4f, -0.7f, 0.0f}, {0.0f, 1.0f}},
        {{-0.4f,  0.7f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.4f, -0.7f, 0.0f}, {1.0f, 1.0f}},
        {{ 0.4f,  0.7f, 0.0f}, {1.0f, 0.0f}}
    };

    std::vector<unsigned short> _indices =
    {
        0, 1, 2,
        1, 3, 2
    };

public:
    std::vector<VertexStruct::Vertex> GetVerticesPtr();
    std::vector<unsigned short> GetIndicesPtr();

    unsigned int GetVerticesCount();
    unsigned int GetVerticesByte();

    unsigned int GetIndicesCount();
    unsigned int GetIndicesByte();

};