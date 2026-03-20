#pragma once

#include<d3d12.h>

class IResourceStates
{
public:
    // リソースステートを返す
    virtual D3D12_RESOURCE_STATES GetResourceStates() = 0;

    IResourceStates() = default;
    ~IResourceStates(){}
};