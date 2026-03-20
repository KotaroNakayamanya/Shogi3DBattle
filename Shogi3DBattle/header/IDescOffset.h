#pragma once

#include<d3d12.h>

class IDescOffset
{
public:
    // ディスクリプタオフセットを返す
    virtual UINT GetDescOffset(ID3D12Device* device) = 0;

    IDescOffset() = default;
    ~IDescOffset(){}
};