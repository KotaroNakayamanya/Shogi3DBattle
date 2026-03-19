#include"CSUHeap.h"

// 指定された位置のディスクリプタハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetDescHandle(UINT i)
{
    auto cpuDescHandle = _csuHeap->GetCPUDescriptorHandleForHeapStart();
    cpuDescHandle.ptr += _descOffset * i;

    return cpuDescHandle;
}

// ヒープを返す
ID3D12DescriptorHeap* CSUHeap::GetCSUHeap(){return _csuHeap.Get();}

CSUHeap::CSUHeap()
{
    _descOffset = 0;
    _cbvNum = 0;
    _srvNum = 0;
    _uavNum = 0;
}

CSUHeap::~CSUHeap(){}