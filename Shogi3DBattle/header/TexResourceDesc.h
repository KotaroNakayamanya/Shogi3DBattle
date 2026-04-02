#pragma once

#include"IResourceDesc.h"

class TexResourceDesc : public IResourceDesc
{
public:
    // テクスチャリソースディスクリプタを返す
    D3D12_RESOURCE_DESC GetResourceDesc(UINT width, UINT height) override;
};