#include"DSVHeapDesc.h"

// DSVヒープディスクリプタを返す
D3D12_DESCRIPTOR_HEAP_DESC DSVHeapDesc::GetHeapDesc(UINT dsvNum)
{
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};

    dsvHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.NumDescriptors = dsvNum;
    

    return dsvHeapDesc;
}

DSVHeapDesc::DSVHeapDesc(){}
DSVHeapDesc::~DSVHeapDesc(){}