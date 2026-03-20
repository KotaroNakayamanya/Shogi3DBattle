#include"HeapFactory.h"
#include"wrl.h"

// ヒープ作成
HRESULT HeapFactory::CreateHeap(Heap* heap, UINT descNum, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heapCom;

    D3D12_DESCRIPTOR_HEAP_DESC desc = _heapDesc->GetHeapDesc(descNum);

    HRESULT result;
    result = device->CreateDescriptorHeap(
        &desc,
        IID_PPV_ARGS(heapCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    heap->SetHeap(heapCom);

    // ディスクリプタオフセット取得
    auto offset = _descOffset->GetDescOffset(device);
    heap->SetDescOffset(offset);

    return S_OK;
}

HeapFactory::HeapFactory(){}
HeapFactory::~HeapFactory(){}