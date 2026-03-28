#include"RenderTexBuffFactory.h"
#include"TexHeapProp.h"
#include"TexResourceDesc.h"
#include"PShaderResourceStates.h"

#include"DefaultHeapProp.h"

// レンダーテクスチャバッファ作成
HRESULT RenderTexBuffFactory::CreateBuff(Buff* constBuff, UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> constBuffCom;

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

    HRESULT result;
    //result = device->CreateCommittedResource(
    //    &heapProp,
    //    D3D12_HEAP_FLAG_NONE,
    //    &resourceDesc,
    //    resourceStates,
    //    &clearValue,
    //    IID_PPV_ARGS(constBuffCom.ReleaseAndGetAddressOf()));
    result = device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        resourceStates,
        &clearValue,
        IID_PPV_ARGS(constBuffCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    constBuff->SetBuff(constBuffCom);
    return S_OK;
}

RenderTexBuffFactory::RenderTexBuffFactory()
{
    _heapProp       = std::make_unique<DefaultHeapProp>();       // デフォルトヒーププロパティ
    _resourceDesc   = std::make_unique<TexResourceDesc>();       // テクスチャリソースディスクリプタ
    _resourceStates = std::make_unique<PShaderResourceStates>(); // ピクセルシェーダーリソースステート
}

RenderTexBuffFactory::~RenderTexBuffFactory(){}