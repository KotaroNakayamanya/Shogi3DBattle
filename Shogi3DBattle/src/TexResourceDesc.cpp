#include"TexResourceDesc.h"

// テクスチャリソースディスクリプタを返す
D3D12_RESOURCE_DESC TexResourceDesc::GetResourceDesc(UINT width, UINT height)
{
    D3D12_RESOURCE_DESC texResourceDesc = {};

    texResourceDesc.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    texResourceDesc.Height           = 256;
    texResourceDesc.Width            = 256;
    texResourceDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
    texResourceDesc.DepthOrArraySize = 1;
    texResourceDesc.MipLevels        = 1;
    texResourceDesc.SampleDesc.Count = 1;

    return texResourceDesc;
}

TexResourceDesc::TexResourceDesc(){}
TexResourceDesc::~TexResourceDesc(){}