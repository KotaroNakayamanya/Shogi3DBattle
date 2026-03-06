#pragma once

#include<d3d12.h>
#include<vector>

#include"VertexStruct.h"

class VertexArg
{
public:
    typedef struct GetCreateVertexObjArg
    {
        ID3D12Device* device;
        unsigned int vertexByte;
        std::vector<VertexStruct::Vertex> vertexPtr;
        unsigned int indexByte;
        std::vector<unsigned short> indexPtr;

    }GetCreateVertexObjArg;

    VertexArg(){}
    ~VertexArg(){}
};