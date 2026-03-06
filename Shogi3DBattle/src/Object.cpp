#include"Object.h"

std::vector<VertexStruct::Vertex> Object::GetVerticesPtr()
{
    return _vertices;
}

std::vector<unsigned short> Object::GetIndicesPtr()
{
    return _indices;
}

unsigned int Object::GetVerticesCount()
{
    return _vertices.size();
}

unsigned int Object::GetVerticesByte()
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

Object::Object(){}
Object::~Object(){}