#include"VertBuffFactory.h"
#include"UploadHeapProp.h"
#include"BuffResourceDesc.h"
#include"ReadResourceStates.h"

// 頂点バッファ作成
HRESULT VertBuffFactory::CreateBuff(Buff* vertBuff, UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> vertBuffCom;

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
        IID_PPV_ARGS(vertBuffCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    vertBuff->SetBuff(vertBuffCom);
    return S_OK;
}

VertBuffFactory::VertBuffFactory()
{
    _heapProp       = std::make_unique<UploadHeapProp>();     // UPLOADヒーププロパティ
    _resourceDesc   = std::make_unique<BuffResourceDesc>();   // バッファリソースディスクリプタ
    _resourceStates = std::make_unique<ReadResourceStates>(); // ジェネリックリード
}

VertBuffFactory::~VertBuffFactory(){}