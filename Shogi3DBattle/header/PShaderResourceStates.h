#pragma once

#include"IResourceStates.h"

class PShaderResourceStates : public IResourceStates
{
public:
    // ピクセルシェーダーリソースステートを返す
    D3D12_RESOURCE_STATES GetResourceStates() override;
};