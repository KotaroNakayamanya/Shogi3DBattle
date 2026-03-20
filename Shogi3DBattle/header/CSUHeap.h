#pragma once

#include"Heap.h"

class CSUHeap : public Heap
{
private:
    UINT _cbvNum; // CBV数
    UINT _srvNum; // SRV数
    UINT _uavNum; // UAV数
   
public:
    // 指定された位置のCBVハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetCBVHandle(UINT i);
    // 指定された位置のGPUCBVハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUCBVHandle(UINT i);
    // 指定された位置のSRVハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetSRVHandle(UINT i);
    // 指定された位置のGPUSRVハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSRVHandle(UINT i);
    // 指定された位置のUAVハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetUAVHandle(UINT i);
    // 指定された位置のGPUUAVハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUUAVHandle(UINT i);

    void SetCBVNum(UINT cbvNum); // CBV数セット
    void SetSRVNum(UINT srvNum); // SRV数セット
    void SetUAVNum(UINT uavNum); // UAV数セット

    CSUHeap();
    ~CSUHeap();
};