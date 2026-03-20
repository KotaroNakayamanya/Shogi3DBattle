#include"DSVOffset.h"

// DSVオフセットを返す
UINT DSVOffset::GetDescOffset(ID3D12Device* device)
{
    return device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

DSVOffset::DSVOffset(){}
DSVOffset::~DSVOffset(){}