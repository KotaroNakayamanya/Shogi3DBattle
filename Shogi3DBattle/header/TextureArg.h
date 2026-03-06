#pragma once

#include<d3d12.h>

class TextureArg
{
public:

    typedef struct CreateTextureObjArg
    {
        ID3D12Device* device;
        DXGI_SAMPLE_DESC sampleDesc;

    }CreateTextureObjArg;

    TextureArg(){}
    ~TextureArg(){}
};