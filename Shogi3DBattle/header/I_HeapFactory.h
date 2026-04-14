#pragma once

#include<memory>
#include"IHeapDesc.h"
#include"IDescOffset.h"
#include"Heap.h"

class I_HeapFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

protected:
    std::unique_ptr<IHeapDesc>   _heapDesc;   // ヒープディスクリプタ
    std::unique_ptr<IDescOffset> _descOffset; // ディスクリプタオフセット

public:
    // ヒープ作成
    ComPtr<ID3D12DescriptorHeap> CreateHeap(UINT descNum, ID3D12Device* device);

    virtual ~I_HeapFactory() = default;
};