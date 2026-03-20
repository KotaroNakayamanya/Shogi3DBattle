#include"RTVFactory.h"

// RTVì¬
void RTVFactory::CreateView(Heap* rtvHeap, UINT i, Buff* backBuff, ID3D12Device* device)
{
    auto rtvHandle = rtvHeap->GetDescHandle(i);

    device->CreateRenderTargetView(
        backBuff->GetBuff(),
        nullptr,
        rtvHandle);
}

RTVFactory::RTVFactory(){}
RTVFactory::~RTVFactory(){}