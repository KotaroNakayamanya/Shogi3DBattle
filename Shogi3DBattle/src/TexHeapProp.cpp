#include"TexHeapProp.h"

// テクスチャヒーププロパティを返す
D3D12_HEAP_PROPERTIES TexHeapProp::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES texHeapProp = {};

    texHeapProp.Type                 = D3D12_HEAP_TYPE_CUSTOM;
    texHeapProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    texHeapProp.MemoryPoolPreference =  D3D12_MEMORY_POOL_L0;

    return texHeapProp;
}

TexHeapProp::TexHeapProp(){}
TexHeapProp::~TexHeapProp(){}