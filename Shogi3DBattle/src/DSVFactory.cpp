#include"DSVFactory.h"

// DSV作成
void DSVFactory::CreateView(Heap* dsvHeap, UINT i, ID3D12Resource* dsBuff, ID3D12Device* device)
{
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = GetDSVDesc();

    device->CreateDepthStencilView(
        dsBuff,
        &dsvDesc,
        dsvHeap->GetDescHandle(i));
}

// DSVディスクリプタ
D3D12_DEPTH_STENCIL_VIEW_DESC DSVFactory::GetDSVDesc()
{
    D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};

    desc.Format = // float値
        DXGI_FORMAT_D32_FLOAT;
    desc.ViewDimension = // 2Dテクスチャ
        D3D12_DSV_DIMENSION_TEXTURE2D;
    desc.Flags =
        D3D12_DSV_FLAG_NONE;

    return desc;
}

DSVFactory::DSVFactory(){}
DSVFactory::~DSVFactory(){}