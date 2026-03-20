#include"UploadHeapProp.h"

// UPLOADヒーププロパティを返す
D3D12_HEAP_PROPERTIES UploadHeapProp::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES uploadHeapProp = {};

    uploadHeapProp.Type =
        D3D12_HEAP_TYPE_UPLOAD;
    uploadHeapProp.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    uploadHeapProp.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return uploadHeapProp;
}

UploadHeapProp::UploadHeapProp(){}
UploadHeapProp::~UploadHeapProp(){}