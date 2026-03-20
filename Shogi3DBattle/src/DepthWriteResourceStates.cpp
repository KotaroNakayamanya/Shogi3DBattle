#include"DepthWriteResourceStates.h"

// デプスライトステートを返す
D3D12_RESOURCE_STATES DepthWriteResourceStates::GetResourceStates()
{
    return D3D12_RESOURCE_STATE_DEPTH_WRITE;
}
    
DepthWriteResourceStates::DepthWriteResourceStates(){}
DepthWriteResourceStates::~DepthWriteResourceStates(){}