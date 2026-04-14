#include"I_HeapFactory.h"
#include"wrl.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// ヒープ作成
ComPtr<ID3D12DescriptorHeap> I_HeapFactory::CreateHeap(UINT descNum, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> comPtr;

    D3D12_DESCRIPTOR_HEAP_DESC desc = _heapDesc->GetHeapDesc(descNum);

    device->CreateDescriptorHeap(
        &desc,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));

    //auto uniquePtr = std::make_unique<Heap>();
    //uniquePtr->SetHeap(heapCom);

    //// ディスクリプタオフセット取得
    //auto offset = _descOffset->GetDescOffset(device);
    //uniquePtr->SetDescOffset(offset);

    return comPtr;
}