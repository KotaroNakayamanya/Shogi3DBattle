#pragma once

#include<memory>
#include"IHeapDesc.h"
#include"IDescOffset.h"
#include"Heap.h"

class HeapFactory
{
protected:
    std::unique_ptr<IHeapDesc>   _heapDesc;   // ヒープディスクリプタ
    std::unique_ptr<IDescOffset> _descOffset; // ディスクリプタオフセット

public:
    // ヒープ作成
    HRESULT CreateHeap(Heap* heap, UINT descNum, ID3D12Device* device);

    HeapFactory();
    ~HeapFactory();
};