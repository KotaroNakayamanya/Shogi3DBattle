#include"RTVFactory.h"

// RTVì¬
void RTVFactory::CreateView(Heap* rtvHeap, UINT i, ID3D12Resource* rtBuff, ID3D12Device* device)
{
    auto rtvHandle = rtvHeap->GetDescHandle(i);

    device->CreateRenderTargetView(
        rtBuff,
        nullptr,
        rtvHandle);
}