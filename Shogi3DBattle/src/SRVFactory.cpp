#include"SRVFactory.h"

// SRV作成
void SRVFactory::CreateView(Heap* csuHeap, UINT i, ID3D12Resource* texBuff, ID3D12Device* device)
{
    auto srvHandle = csuHeap->GetDescHandle(i);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = GetSRVDesc();

    device->CreateShaderResourceView(
        texBuff,
        &srvDesc,
        srvHandle);
}

// SRVディスクリプタ
D3D12_SHADER_RESOURCE_VIEW_DESC SRVFactory::GetSRVDesc()
{
    D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Shader4ComponentMapping =
        D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    desc.ViewDimension =
        D3D12_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels =
        1;

    return desc;
}