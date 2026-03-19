#include"DSVHeap.h"

// DSVƒnƒ“ƒhƒ‹‚ð•Ô‚·
D3D12_CPU_DESCRIPTOR_HANDLE DSVHeap::GetDSVHandle()
{
    return _dsvHeap->GetCPUDescriptorHandleForHeapStart();
}

DSVHeap::DSVHeap(){}
DSVHeap::~DSVHeap(){}