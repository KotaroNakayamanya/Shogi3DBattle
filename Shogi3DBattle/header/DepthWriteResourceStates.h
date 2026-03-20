#pragma once

#include"IResourceStates.h"

class DepthWriteResourceStates : public IResourceStates
{
public:
    // デプスライトステートを返す
    D3D12_RESOURCE_STATES GetResourceStates() override;
    
    DepthWriteResourceStates();
    ~DepthWriteResourceStates();
};