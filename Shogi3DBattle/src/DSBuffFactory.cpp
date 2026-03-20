#include"DSBuffFactory.h"
#include"DefaultHeapProp.h"
#include"DSResourceDesc.h"
#include"DepthWriteResourceStates.h"

// デプスステンシルバッファ作成
HRESULT DSBuffFactory::CreateBuff(Buff* constBuff, UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> constBuffCom;

    D3D12_HEAP_PROPERTIES heapProp       = _heapProp->GetHeapProp();
    D3D12_RESOURCE_DESC   resourceDesc   = _resourceDesc->GetResourceDesc(width, height);
    D3D12_RESOURCE_STATES resourceStates = _resourceStates->GetResourceStates();
    D3D12_CLEAR_VALUE     clearValue     = {};

    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.Format             = DXGI_FORMAT_D32_FLOAT;

    HRESULT result;
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

DSBuffFactory::DSBuffFactory()
{
    _heapProp       = std::make_unique<DefaultHeapProp>();          // DEFAULTヒーププロパティ
    _resourceDesc   = std::make_unique<DSResourceDesc>();           // デプスステンシルリソースディスクリプタ
    _resourceStates = std::make_unique<DepthWriteResourceStates>(); // デプスライトリソースステート
}

DSBuffFactory::~DSBuffFactory(){}