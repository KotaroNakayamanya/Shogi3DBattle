#pragma once

#include"IViewFactory.h"

class RTVFactory : public IViewFactory
{
public:
    // RTVçÏê¨
    void CreateView(Heap* rtvHeap, UINT i, ID3D12Resource* rtID3D12Resource, ID3D12Device* device) override;
};