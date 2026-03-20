#pragma once

#include"IViewFactory.h"

class SRVFactory : public IViewFactory
{
private:
    // SRVディスクリプタ
    D3D12_SHADER_RESOURCE_VIEW_DESC GetSRVDesc();

public:
    // SRV作成
    void CreateView(Heap* csuHeap, UINT i, Buff* texBuff, ID3D12Device* device) override;

    SRVFactory();
    ~SRVFactory();
};