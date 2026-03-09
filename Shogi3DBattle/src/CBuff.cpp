#include"CBuff.h"

// コンスタントオブジェクト作成
HRESULT CBuff::CreateCBuffObj(ID3D12Device* device, UINT verticesByteSize)
{
    D3D12_HEAP_PROPERTIES heapProp =
        GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc =
        GetResourceDesc(verticesByteSize);

    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_cBuff.ReleaseAndGetAddressOf()));
}

// ヒーププロパティ
D3D12_HEAP_PROPERTIES CBuff::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

// リソースディスクリプタ
D3D12_RESOURCE_DESC CBuff::GetResourceDesc(UINT verticesByte)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Height =
        1;
    desc.Width =
        (verticesByte + 0xff) & ~0xff;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count =
        1;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    return desc;
}




// バッファを返す
ID3D12Resource* CBuff::GetBuff(){return _cBuff.Get();}




CBuff::CBuff(){}
CBuff::~CBuff(){}