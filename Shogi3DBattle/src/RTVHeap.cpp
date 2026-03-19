#include"RTVHeap.h"

// ˆø”‚ÌˆÊ’u‚ÌRTVƒnƒ“ƒhƒ‹‚ð•Ô‚·
D3D12_CPU_DESCRIPTOR_HANDLE RTVHeap::GetRTVHandle(UINT i)
{
    auto rtvHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += _rtvOffset * i;

    return rtvHandle;
}

RTVHeap::RTVHeap(){}
RTVHeap::~RTVHeap(){}