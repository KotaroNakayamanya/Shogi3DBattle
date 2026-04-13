#include"DSBuffFactory.h"
#include"DefaultHeapProp.h"
#include"DSResourceDesc.h"
#include"DepthWriteResourceStates.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// デプスステンシルバッファ作成
ComPtr<ID3D12Resource> DSBuffFactory::CreateBuff(UINT width, UINT height, ID3D12Device* device)
{
    Microsoft::WRL::ComPtr<ID3D12Resource> comPtr;

    D3D12_HEAP_PROPERTIES heapProp       = _heapProp->GetHeapProp();
    D3D12_RESOURCE_DESC   resourceDesc   = _resourceDesc->GetResourceDesc(width, height);
    D3D12_RESOURCE_STATES resourceStates = _resourceStates->GetResourceStates();
    D3D12_CLEAR_VALUE     clearValue     = {};

    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.Format             = DXGI_FORMAT_D32_FLOAT;

    device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        resourceStates,
        &clearValue,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));

    return comPtr;
}

DSBuffFactory::DSBuffFactory()
{
    _heapProp       = std::make_unique<DefaultHeapProp>();          // DEFAULTヒーププロパティ
    _resourceDesc   = std::make_unique<DSResourceDesc>();           // デプスステンシルリソースディスクリプタ
    _resourceStates = std::make_unique<DepthWriteResourceStates>(); // デプスライトリソースステート
}