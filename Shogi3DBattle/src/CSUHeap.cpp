#include"CSUHeap.h"

// 指定された位置のCBVハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetCBVHandle(UINT i){return GetDescHandle(i);}
// 指定された位置のGPUCBVハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE CSUHeap::GetGPUCBVHandle(UINT i){return GetGPUDescHandle(i);}
// 指定された位置のSRVハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetSRVHandle(UINT i){return GetDescHandle(_cbvNum + i);}
// 指定された位置のGPUSRVハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE CSUHeap::GetGPUSRVHandle(UINT i){return GetGPUDescHandle(_cbvNum + i);}
// 指定された位置のUAVハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetUAVHandle(UINT i){return GetDescHandle(_cbvNum + _srvNum + i);}
// 指定された位置のGPUUAVハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE CSUHeap::GetGPUUAVHandle(UINT i){return GetGPUDescHandle(_cbvNum + _srvNum + i);}

// CBV数セット
void CSUHeap::SetCBVNum(UINT cbvNum){_cbvNum = cbvNum;}
// SRV数セット
void CSUHeap::SetSRVNum(UINT srvNum){_srvNum = srvNum;}
// UAV数セット
void CSUHeap::SetUAVNum(UINT uavNum){_uavNum = uavNum;}

CSUHeap::CSUHeap(){}
CSUHeap::~CSUHeap(){}