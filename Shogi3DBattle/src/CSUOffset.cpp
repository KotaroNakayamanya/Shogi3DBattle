#include"CSUOffset.h"

// CSUオフセットを返す
UINT CSUOffset::GetDescOffset(ID3D12Device* device)
{
    return device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

CSUOffset::CSUOffset(){}
CSUOffset::~CSUOffset(){}