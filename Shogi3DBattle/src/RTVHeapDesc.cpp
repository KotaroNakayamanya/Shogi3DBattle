#include"RTVHeapDesc.h"

// RTVヒープディスクリプタを返す
D3D12_DESCRIPTOR_HEAP_DESC RTVHeapDesc::GetHeapDesc(UINT rtvNum)
{
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};

    rtvHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.NodeMask       = 0;
    rtvHeapDesc.NumDescriptors = rtvNum;
    rtvHeapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return rtvHeapDesc;
}

RTVHeapDesc::RTVHeapDesc(){}
RTVHeapDesc::~RTVHeapDesc(){}