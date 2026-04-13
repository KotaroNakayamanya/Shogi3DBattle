#include"RenderTexBuffFactory.h"
#include"DefaultHeapProp.h"
#include"TexResourceDesc.h"
#include"PShaderResourceStates.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// レンダーテクスチャバッファ作成
ComPtr<ID3D12Resource> RenderTexBuffFactory::CreateBuff(UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> comPtr;

    D3D12_HEAP_PROPERTIES heapProp       = _heapProp->GetHeapProp();
    D3D12_RESOURCE_DESC   resourceDesc   = _resourceDesc->GetResourceDesc(width, height);
    D3D12_RESOURCE_STATES resourceStates = _resourceStates->GetResourceStates();
    D3D12_CLEAR_VALUE     clearValue     = {};

    clearValue.Color[0] = 1.0f;
    clearValue.Color[1] = 1.0f;
    clearValue.Color[2] = 1.0f;
    clearValue.Color[3] = 1.0f;
    clearValue.Format   = DXGI_FORMAT_R8G8B8A8_UNORM;

    resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        resourceStates,
        &clearValue,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));

    return comPtr;
}

RenderTexBuffFactory::RenderTexBuffFactory()
{
    _heapProp       = std::make_unique<DefaultHeapProp>();       // デフォルトヒーププロパティ
    _resourceDesc   = std::make_unique<TexResourceDesc>();       // テクスチャリソースディスクリプタ
    _resourceStates = std::make_unique<PShaderResourceStates>(); // ピクセルシェーダーリソースステート
}