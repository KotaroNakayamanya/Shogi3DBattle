#pragma once

#include"IViewFactory.h"

class RTVFactory : public IViewFactory
{
public:
    // RTVçÏê¨
    void CreateView(Heap* rtvHeap, UINT i, Buff* rtBuff, ID3D12Device* device) override;

    RTVFactory();
    ~RTVFactory();
};