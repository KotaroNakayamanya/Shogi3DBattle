#include"TexBuffFactory.h"
#include"TexHeapProp.h"
#include"TexResourceDesc.h"
#include"PShaderResourceStates.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// テクスチャバッファ作成
ComPtr<ID3D12Resource> TexBuffFactory::CreateBuff(UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> comPtr;

    D3D12_HEAP_PROPERTIES heapProp       = _heapProp->GetHeapProp();
    D3D12_RESOURCE_DESC   resourceDesc   = _resourceDesc->GetResourceDesc(width, height);
    D3D12_RESOURCE_STATES resourceStates = _resourceStates->GetResourceStates();

    device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        resourceStates,
        nullptr,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));

    return comPtr;
}

TexBuffFactory::TexBuffFactory()
{
    _heapProp       = std::make_unique<TexHeapProp>();           // テクスチャヒーププロパティ
    _resourceDesc   = std::make_unique<TexResourceDesc>();       // テクスチャリソースディスクリプタ
    _resourceStates = std::make_unique<PShaderResourceStates>(); // ピクセルシェーダーリソースステート
}