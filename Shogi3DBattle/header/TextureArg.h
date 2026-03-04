#pragma once

#include<d3d12.h>

class TextureArg
{
public:

    typedef struct CreateTextureObjArg
    {
        ID3D12Device* device;

        //D3D12_HEAP_PROPERTIES heapProp;
        //D3D12_RESOURCE_DESC   resourceDesc;

        //D3D12_DESCRIPTOR_HEAP_DESC heapDesc;

        //D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
        DXGI_SAMPLE_DESC sampleDesc;

    }CreateTextureObjArg;
};