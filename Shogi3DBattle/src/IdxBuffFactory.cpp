#include"IdxBuffFactory.h"
#include"UploadHeapProp.h"
#include"BuffResourceDesc.h"
#include"ReadResourceStates.h"

// インデックスバッファ作成
HRESULT IdxBuffFactory::CreateBuff(Buff* idxBuff, UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> idxBuffCom;

    D3D12_HEAP_PROPERTIES heapProp       = _heapProp->GetHeapProp();
    D3D12_RESOURCE_DESC   resourceDesc   = _resourceDesc->GetResourceDesc(width, height);
    D3D12_RESOURCE_STATES resourceStates = _resourceStates->GetResourceStates();

    HRESULT result;
    result = device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        resourceStates,
        nullptr,
        IID_PPV_ARGS(idxBuffCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    idxBuff->SetBuff(idxBuffCom);
    return S_OK;
}

IdxBuffFactory::IdxBuffFactory()
{
    _heapProp       = std::make_unique<UploadHeapProp>();     // UPLOADヒーププロパティ
    _resourceDesc   = std::make_unique<BuffResourceDesc>();   // バッファリソースディスクリプタ
    _resourceStates = std::make_unique<ReadResourceStates>(); // ジェネリックリード
}

IdxBuffFactory::~IdxBuffFactory(){}