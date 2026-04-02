#pragma once

#include<d3d12.h>

class IResourceDesc
{
public:
    // リソースディスクリプタを返す
    virtual D3D12_RESOURCE_DESC GetResourceDesc(UINT width, UINT height) = 0;

    virtual ~IResourceDesc() = default;
};