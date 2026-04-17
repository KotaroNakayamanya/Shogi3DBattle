#pragma once

#include"Heap.h"

class CSUHeap : public Heap
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    unsigned int _cbvNum; // CBV数
    unsigned int _srvNum; // SRV数
    unsigned int _uavNum; // UAV数
   
public:
    D3D12_CPU_DESCRIPTOR_HANDLE GetCBVHandle(unsigned int i);    // 指定された位置のCBVハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUCBVHandle(unsigned int i); // 指定された位置のGPUCBVハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetSRVHandle(unsigned int i);    // 指定された位置のSRVハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSRVHandle(unsigned int i); // 指定された位置のGPUSRVハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetUAVHandle(unsigned int i);    // 指定された位置のUAVハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUUAVHandle(unsigned int i); // 指定された位置のGPUUAVハンドルを返す

    unsigned int GetCBVStartIdx(); // CBVのスタート位置のインデックスを返す
    unsigned int GetSRVStartIdx(); // SRVのスタート位置のインデックスを返す
    unsigned int GetUAVStartIdx(); // UAVのスタート位置のインデックスを返す

    void SetCBVNum(unsigned int cbvNum); // CBV数セット
    unsigned int GetCBVNum();            // CBV数を返す
    void SetSRVNum(unsigned int srvNum); // SRV数セット
    unsigned int GetSRVNum();            // SRV数を返す
    void SetUAVNum(unsigned int uavNum); // UAV数セット
    unsigned int GetUAVNum();            // UAV数を返す

    CSUHeap(
        const Heap&                  heap,
        unsigned int                 cbvNum,
        unsigned int                 srvNum,
        unsigned int                 uavNum);
};