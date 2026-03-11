#include"DSVHeap.h"
#include<cassert>

// DSVヒープ作成
HRESULT DSVHeap::CreateDSVHeap(
    ID3D12Device* device, ID3D12Resource* dsBuff)
{
    HRESULT result;

    // DSVヒープ作成
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = GetDSVHeapDesc();

    result = device->CreateDescriptorHeap(
        &dsvHeapDesc,
        IID_PPV_ARGS(_dsvHeap.ReleaseAndGetAddressOf()));
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    // ビュー作成
    CreateDSV(device, dsBuff);
    
    return S_OK;
}

// DSVヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC DSVHeap::GetDSVHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};

    desc.NumDescriptors =
        1;
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

    return desc;
}

// DSV作成
void DSVHeap::CreateDSV(ID3D12Device* device, ID3D12Resource* dsBuff)
{
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc =  GetDSVDesc();

    device->CreateDepthStencilView(
        dsBuff,
        &dsvDesc,
        _dsvHeap->GetCPUDescriptorHandleForHeapStart());
}

// DSVディスクリプタ
D3D12_DEPTH_STENCIL_VIEW_DESC DSVHeap::GetDSVDesc()
{
    D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};

    desc.Format = // float値
        DXGI_FORMAT_D32_FLOAT;
    desc.ViewDimension = // 2Dテクスチャ
        D3D12_DSV_DIMENSION_TEXTURE2D;
    desc.Flags =
        D3D12_DSV_FLAG_NONE;

    return desc;
}




// DSVハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE DSVHeap::GetDSVStartHandle()
{
    return _dsvHeap->GetCPUDescriptorHandleForHeapStart();
}




// DSVヒープを返す
ID3D12DescriptorHeap* DSVHeap::GetDSVHeap(){return _dsvHeap.Get();}




DSVHeap::DSVHeap(){}
DSVHeap::~DSVHeap(){}