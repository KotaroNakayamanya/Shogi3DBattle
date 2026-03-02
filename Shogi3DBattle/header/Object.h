#pragma once

#include<DirectXMath.h>
#include<vector>

class Object
{
private:
    std::vector<DirectX::XMFLOAT3> _vertices =
    {
        {-1.0f, -1.0f, 0.0f},
        {-1.0f,  1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f},
        { 0.9f,  0.9f, 0.0f}
    };

    std::vector<unsigned short> _indices =
    {
        0, 1, 2,
        1, 3, 2
    };

public:
    std::vector<DirectX::XMFLOAT3> GetVerticesPtr();
    std::vector<unsigned short> GetIndicesPtr();

    unsigned int GetVerticesCount();
    unsigned int GetVerticesByte();

    unsigned int GetIndicesCount();
    unsigned int GetIndicesByte();
};