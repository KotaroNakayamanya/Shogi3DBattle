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

    UINT GetCBVStartIdx(); // CBVのスタート位置のインデックスを返す
    UINT GetSRVStartIdx(); // SRVのスタート位置のインデックスを返す
    UINT GetUAVStartIdx(); // UAVのスタート位置のインデックスを返す

    void SetCBVNum(UINT cbvNum); // CBV数セット
    UINT GetCBVNum();            // CBV数を返す
    void SetSRVNum(UINT srvNum); // SRV数セット
    UINT GetSRVNum();            // SRV数を返す
    void SetUAVNum(UINT uavNum); // UAV数セット
    UINT GetUAVNum();            // UAV数を返す

    CSUHeap();
    ~CSUHeap();
};