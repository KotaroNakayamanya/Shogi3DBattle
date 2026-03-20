#include"DefaultHeapProp.h"

// DEFAULTヒーププロパティを返す
D3D12_HEAP_PROPERTIES DefaultHeapProp::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES defaultHeapProp = {};

    defaultHeapProp.Type                 = D3D12_HEAP_TYPE_DEFAULT;
    defaultHeapProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    defaultHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    return defaultHeapProp;
}

DefaultHeapProp::DefaultHeapProp(){}
DefaultHeapProp::~DefaultHeapProp(){}