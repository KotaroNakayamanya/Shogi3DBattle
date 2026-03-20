#pragma once

#include"IResourceDesc.h"

class DSResourceDesc : public IResourceDesc
{
public:
    // デプスステンシルディスクリプタを返す
    D3D12_RESOURCE_DESC GetResourceDesc(UINT width, UINT height) override;

    DSResourceDesc();
    ~DSResourceDesc();
};