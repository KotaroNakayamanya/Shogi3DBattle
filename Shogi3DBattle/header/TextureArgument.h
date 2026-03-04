#pragma once

#include<d3d12.h>

class TextureArgument
{
public:

    typedef struct CreateTextureObjectArgument
    {
        ID3D12Device* device;

        D3D12_HEAP_PROPERTIES heapProperty;
        D3D12_RESOURCE_DESC   resourceDesc;

        D3D12_DESCRIPTOR_HEAP_DESC heapDesc;

        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;

    }CreateTextureObjectArgument;
};