#include"I_HeapFactory.h"
#include<cassert>
#include<wrl.h>

// ヒープ作成
std::unique_ptr<Heap> I_HeapFactory::CreateHeap(UINT descNum, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> comPtr;

    D3D12_DESCRIPTOR_HEAP_DESC desc = _heapDesc->GetHeapDesc(descNum);

    HRESULT result;
    result = device->CreateDescriptorHeap(
        &desc,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));
    assert(SUCCEEDED(result));

    // ディスクリプタオフセット取得
    auto offset = _descOffset->GetDescOffset(device);

    return std::make_unique<Heap>(comPtr, offset);
}