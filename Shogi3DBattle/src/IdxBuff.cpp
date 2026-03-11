#include"IdxBuff.h"
#include<cassert>
#include<memory>

// インデックスバッファ作成
HRESULT IdxBuff::CreateIdxBuff(ID3D12Device* device, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetVertexHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetVertexResourceDesc(byteSize);

    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_idxBuff.ReleaseAndGetAddressOf()));

}

// ヒーププロパティ
D3D12_HEAP_PROPERTIES IdxBuff::GetVertexHeapProp()
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
D3D12_RESOURCE_DESC IdxBuff::GetVertexResourceDesc(UINT byteSize)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width =
        byteSize;
    desc.Height =
        1;
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




// インデックスバッファに書き込み
HRESULT IdxBuff::WriteIdxBuff(std::vector<unsigned short> indexPtr)
{
    std::shared_ptr<unsigned short> idxMap;

    HRESULT result = _idxBuff->Map(
        0, nullptr, (void**)&idxMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto indices = indexPtr;
    
    std::copy(indices.begin(), indices.end(), idxMap.get());

    _idxBuff->Unmap(0, nullptr);
    
    return S_OK;
}




// インデックスバッファを返す
ID3D12Resource* IdxBuff::GetIdxBuff(){return _idxBuff.Get();}




IdxBuff::IdxBuff(){}
IdxBuff::~IdxBuff(){}