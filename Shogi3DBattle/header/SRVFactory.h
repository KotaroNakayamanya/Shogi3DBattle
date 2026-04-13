#pragma once

#include"IViewFactory.h"

class SRVFactory : public IViewFactory
{
private:
    // SRVディスクリプタ
    D3D12_SHADER_RESOURCE_VIEW_DESC GetSRVDesc();

public:
    // SRV作成
    void CreateView(Heap* csuHeap, UINT i, ID3D12Resource* texID3D12Resource, ID3D12Device* device) override;
};