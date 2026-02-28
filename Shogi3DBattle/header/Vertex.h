#pragma once

#include<DirectXMath.h>
#include<vector>

class Vertex
{
private:
    std::vector<DirectX::XMFLOAT3> _vertices =
    {
        {-1.0f, -1.0f, 0.0f},
        {-1.0f,  1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f}
    };


public:
    std::vector<DirectX::XMFLOAT3> GetVerticesPtr();
};