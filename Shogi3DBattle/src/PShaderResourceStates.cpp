#include"PShaderResourceStates.h"

// ピクセルシェーダリソースステートを返す
D3D12_RESOURCE_STATES PShaderResourceStates::GetResourceStates()
{
    return D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
}
    
PShaderResourceStates::PShaderResourceStates(){}
PShaderResourceStates::~PShaderResourceStates(){}