
#include"CBVFactory.h"

// CBV作成
void CBVFactory::CreateView(Heap* csuHeap, UINT i, Buff* constBuff, ID3D12Device* device)
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = GetCBVDesc(constBuff->GetBuff());

    auto cbvHandle = csuHeap->GetDescHandle(i);

    device->CreateConstantBufferView(
        &cbvDesc,
        cbvHandle);
}

// CBVディスクリプタ
D3D12_CONSTANT_BUFFER_VIEW_DESC CBVFactory::GetCBVDesc(ID3D12Resource* constBuff)
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};

    desc.BufferLocation = constBuff->GetGPUVirtualAddress();
    desc.SizeInBytes    = static_cast<UINT>(constBuff->GetDesc().Width * constBuff->GetDesc().Height);

    return desc;
}

CBVFactory::CBVFactory(){}
CBVFactory::~CBVFactory(){}