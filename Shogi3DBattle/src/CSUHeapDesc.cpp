#include"CSUHeapDesc.h"

// CSUヒープディスクリプタを返す
D3D12_DESCRIPTOR_HEAP_DESC CSUHeapDesc::GetHeapDesc(UINT csuNum)
{
    D3D12_DESCRIPTOR_HEAP_DESC csuHeapDesc = {};

    csuHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    csuHeapDesc.NodeMask       = 0;
    csuHeapDesc.NumDescriptors = csuNum;
    csuHeapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    return csuHeapDesc;
}

CSUHeapDesc::CSUHeapDesc(){}
CSUHeapDesc::~CSUHeapDesc(){}