#include"RTVFactory.h"

// RTVì¬
void RTVFactory::CreateView(Heap* rtvHeap, UINT i, Buff* rtBuff, ID3D12Device* device)
{
    auto rtvHandle = rtvHeap->GetDescHandle(i);

    device->CreateRenderTargetView(
        rtBuff->GetBuff(),
        nullptr,
        rtvHandle);
}

RTVFactory::RTVFactory(){}
RTVFactory::~RTVFactory(){}