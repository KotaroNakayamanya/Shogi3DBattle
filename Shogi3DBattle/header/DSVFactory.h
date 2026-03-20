#pragma once

#include"IViewFactory.h"

class DSVFactory : public IViewFactory
{
private:
    // DSVディスクリプタ
    D3D12_DEPTH_STENCIL_VIEW_DESC GetDSVDesc();

public:
    // DSV作成
    void CreateView(Heap* dsvHeap, UINT i, Buff* dsBuff, ID3D12Device* device) override;

    DSVFactory();
    ~DSVFactory();
};