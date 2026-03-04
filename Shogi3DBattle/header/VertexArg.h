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
        D3D12_HEAP_PROPERTIES heapProp;
        D3D12_RESOURCE_DESC   resourceDesc;
        unsigned int vertexByte;
        std::vector<VertexStruct::Vertex> vertexPtr;
        unsigned int indexByte;
        std::vector<unsigned short> indexPtr;

    }GetCreateVertexObjArg;
};