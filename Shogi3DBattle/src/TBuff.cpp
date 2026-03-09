#include"TBuff.h"

#include<vector>
#include<cassert>

#include "TextureStruct.h"

// テクスチャバッファオブジェクト作成
HRESULT TBuff::CreateTBuffObj(TextureArg::CreateTextureObjArg arg)
{
    D3D12_HEAP_PROPERTIES heapProp = GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetResourceDesc(arg.sampleDesc);
 
    return arg.device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, // テクスチャ
        nullptr,
        IID_PPV_ARGS(_tBuff.ReleaseAndGetAddressOf()));
}

// テクスチャヒーププロパティ
D3D12_HEAP_PROPERTIES TBuff::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_CUSTOM;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    prop.MemoryPoolPreference = // 転送L0
        D3D12_MEMORY_POOL_L0;
    prop.CreationNodeMask =
        0;
    prop.VisibleNodeMask =
        0;

    return prop;
}

// テクスチャリソースディスクリプタ
D3D12_RESOURCE_DESC TBuff::GetResourceDesc(DXGI_SAMPLE_DESC sampleDesc)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    desc.Height =
        256;
    desc.Width =
        256;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;  
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_UNKNOWN;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.SampleDesc =
        sampleDesc;

    return desc;
}




// バッファを渡す
ID3D12Resource* TBuff::GetTBuff(){return _tBuff.Get();}




TBuff::TBuff(){}
TBuff::~TBuff(){}