#include"TexBuffFactory.h"
#include"TexHeapProp.h"
#include"TexResourceDesc.h"
#include"PShaderResourceStates.h"

// テクスチャバッファ作成
HRESULT TexBuffFactory::CreateBuff(Buff* texBuff, UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> constBuffCom;

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
        IID_PPV_ARGS(constBuffCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    texBuff->SetBuff(constBuffCom);
    return S_OK;
}

TexBuffFactory::TexBuffFactory()
{
    _heapProp       = std::make_unique<TexHeapProp>();           // テクスチャヒーププロパティ
    _resourceDesc   = std::make_unique<TexResourceDesc>();       // テクスチャリソースディスクリプタ
    _resourceStates = std::make_unique<PShaderResourceStates>(); // ピクセルシェーダーリソースステート
}