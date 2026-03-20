#include"Heap.h"

// 引数の位置のディスクリプタハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE Heap::GetDescHandle(UINT i)
{
    auto descHandle = _heap->GetCPUDescriptorHandleForHeapStart();
    descHandle.ptr += _descOffset * i;

    return descHandle;
}

// 引数の位置のGPUディスクリプタハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE Heap::GetGPUDescHandle(UINT i)
{
    auto gpuDescHandle = _heap->GetGPUDescriptorHandleForHeapStart();
    gpuDescHandle.ptr += _descOffset * i;

    return gpuDescHandle;
}

// ヒープセット
void Heap::SetHeap(ComPtr<ID3D12DescriptorHeap> heap){_heap = heap;}
// ヒープを返す
ID3D12DescriptorHeap* Heap::GetHeap(){return _heap.Get();}
// ディスクリプタオフセットセット
void Heap::SetDescOffset(UINT descOffset){_descOffset = descOffset;}

Heap::Heap(){}
Heap::~Heap(){}