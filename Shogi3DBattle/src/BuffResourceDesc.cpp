#include"BuffResourceDesc.h"

// バッファリソースディスクリプタを返す
D3D12_RESOURCE_DESC BuffResourceDesc::GetResourceDesc(UINT width, UINT height)
{
    D3D12_RESOURCE_DESC buffResourceDesc = {};

    buffResourceDesc.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER;
    buffResourceDesc.Width            = width;
    buffResourceDesc.Height           = height;
    buffResourceDesc.DepthOrArraySize = 1;
    buffResourceDesc.MipLevels        = 1;
    buffResourceDesc.SampleDesc.Count = 1;
    buffResourceDesc.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    return buffResourceDesc;
}