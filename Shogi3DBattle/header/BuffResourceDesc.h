#pragma once

#include"IResourceDesc.h"

class BuffResourceDesc : public IResourceDesc
{
public:
    // バッファリソースディスクリプタを返す
    D3D12_RESOURCE_DESC GetResourceDesc(UINT width, UINT height) override;

    BuffResourceDesc();
    ~BuffResourceDesc();
};