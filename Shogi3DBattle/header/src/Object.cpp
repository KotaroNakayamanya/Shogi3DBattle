#include"Object.h"

std::vector<DirectX::XMFLOAT3> Object::GetVerticesPtr()
{
    return _vertices;
}

std::vector<unsigned short> Object::GetIndicesPtr()
{
    return _indices;
}

unsigned int Object::GetVertexCount()
{
    return _vertices.size();
}

unsigned int Object::GetVertexByte()
{
    return sizeof(_vertices[0]);
}

unsigned int Object::GetIndicesCount()
{
    return _indices.size();
}

unsigned int Object::GetIndicesByte()
{
    return _indices.size() * sizeof(_indices[0]);
}