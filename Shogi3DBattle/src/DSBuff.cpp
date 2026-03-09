#include"DSBuff.h"

// デプスステンシルオブジェクト作成
HRESULT DSBuff::CreateDSBuffObj(
    ID3D12Device* device, UINT windowWidth, UINT windowHeight)
{
    D3D12_HEAP_PROPERTIES heapProp =
        GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc =
        GetResourceDesc(windowWidth, windowHeight);
    D3D12_CLEAR_VALUE clearValue =
        GetClearValue();
 
    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE, 
        &clearValue,
        IID_PPV_ARGS(_dsBuff.ReleaseAndGetAddressOf()));
}

// デプスステンシルヒーププロパティ
D3D12_HEAP_PROPERTIES DSBuff::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_DEFAULT;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

// デプスステンシルリソースディスクリプタ
D3D12_RESOURCE_DESC DSBuff::GetResourceDesc(
    UINT windowWidth, UINT windowHeight)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    desc.Width =
        windowWidth;
    desc.Height =
        windowHeight;
    desc.DepthOrArraySize =
        1;
    desc.Format = // 深度値書き込み用
        DXGI_FORMAT_D32_FLOAT;  
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_UNKNOWN;
    desc.Flags = // デプスステンシルとして使用
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    desc.SampleDesc =
        GetSampleDesc();

    return desc;
}

// サンプリングディスクリプタ
DXGI_SAMPLE_DESC DSBuff::GetSampleDesc()
{
    DXGI_SAMPLE_DESC desc = {};

    desc.Count   = 1; // サンプリング数
    desc.Quality = 0; // クオリティ（0は最低）

    return desc;
}

// クリアバリュー
D3D12_CLEAR_VALUE DSBuff::GetClearValue()
{
    D3D12_CLEAR_VALUE clearValue = {};

    clearValue.DepthStencil.Depth = // 深さの初期値を最大値に
        1.0f;
    clearValue.Format = // float値
        DXGI_FORMAT_D32_FLOAT;

    return clearValue;
}




// デプスステンシルバッファを返す
ID3D12Resource* DSBuff::GetDSBuff(){return _dsBuff.Get();}




DSBuff::DSBuff(){}
DSBuff::~DSBuff(){}