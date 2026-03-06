#pragma once

#include<d3d12.h>

class PipelineArg
{
public:
    typedef struct CreatePipelineStateArg
    {
        ID3D12Device* device;

        ID3D12RootSignature* rootSignature;

        ID3DBlob* vertexShaderBlob;
        ID3DBlob* pixelShaderBlob;

        DXGI_SAMPLE_DESC sampleDesc;

    }CreatePipelineStateArg;

    PipelineArg(){}
    ~PipelineArg(){}
};