#pragma once

#include"IViewFactory.h"

class CBVFactory : public IViewFactory
{
private:
    // CBVディスクリプタ
    D3D12_CONSTANT_BUFFER_VIEW_DESC GetCBVDesc(ID3D12Resource* constBuff);

public:
    // CBV作成
    void CreateView(Heap* csuHeap, UINT i, ID3D12Resource* constID3D12Resource, ID3D12Device* device) override;

    CBVFactory();
    ~CBVFactory();
};