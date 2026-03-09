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
        UINT vertexByte;
        std::vector<VertexStruct::Vertex> vertexPtr;
        UINT indicesByte;
        std::vector<unsigned short> indexPtr;

    }GetCreateVertexObjArg;

    VertexArg(){}
    ~VertexArg(){}
};