#pragma once

#include"IResourceStates.h"

class ReadResourceStates : public IResourceStates
{
public:
    // ジェネリックリードステートを返す
    D3D12_RESOURCE_STATES GetResourceStates() override;
};