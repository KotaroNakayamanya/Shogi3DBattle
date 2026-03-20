#include"DSResourceDesc.h"

// バッファリソースディスクリプタを返す
D3D12_RESOURCE_DESC DSResourceDesc::GetResourceDesc(UINT width, UINT height)
{
    D3D12_RESOURCE_DESC dsResourceDesc = {};

    dsResourceDesc.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    dsResourceDesc.Width            = width;
    dsResourceDesc.Height           = height;
    dsResourceDesc.Format           = DXGI_FORMAT_D32_FLOAT;
    dsResourceDesc.DepthOrArraySize = 1;
    dsResourceDesc.Flags            = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;    
    dsResourceDesc.SampleDesc.Count = 1;

    return dsResourceDesc;
}

DSResourceDesc::DSResourceDesc(){}
DSResourceDesc::~DSResourceDesc(){}