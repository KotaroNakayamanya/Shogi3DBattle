#include"RTVOffset.h"

// RTVオフセットを返す
UINT RTVOffset::GetDescOffset(ID3D12Device* device)
{
    return device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

RTVOffset::RTVOffset(){}
RTVOffset::~RTVOffset(){}