#include"CSUHeap.h"
#include<memory>

D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetCBVHandle   (unsigned int i){return GetDescHandle   (i);} // 指定された位置のCBVハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE CSUHeap::GetGPUCBVHandle(unsigned int i){return GetGPUDescHandle(i);} // 指定された位置のGPUCBVハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetSRVHandle   (unsigned int i){return GetDescHandle   (_cbvNum + i);} // 指定された位置のSRVハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE CSUHeap::GetGPUSRVHandle(unsigned int i){return GetGPUDescHandle(_cbvNum + i);} // 指定された位置のGPUSRVハンドルを返す
D3D12_CPU_DESCRIPTOR_HANDLE CSUHeap::GetUAVHandle   (unsigned int i){return GetDescHandle   (_cbvNum + _srvNum + i);} // 指定された位置のUAVハンドルを返す
D3D12_GPU_DESCRIPTOR_HANDLE CSUHeap::GetGPUUAVHandle(unsigned int i){return GetGPUDescHandle(_cbvNum + _srvNum + i);} // 指定された位置のGPUUAVハンドルを返す

unsigned int CSUHeap::GetCBVStartIdx(){return 0;} // CBVのスタート位置のインデックスを返す
unsigned int CSUHeap::GetSRVStartIdx(){return _cbvNum;} // SRVのスタート位置のインデックスを返す
unsigned int CSUHeap::GetUAVStartIdx(){return _cbvNum + _srvNum;} // UAVのスタート位置のインデックスを返す

void CSUHeap::SetCBVNum(unsigned int cbvNum){_cbvNum = cbvNum;} // CBV数セット
unsigned int CSUHeap::GetCBVNum()           {return _cbvNum;} // CBV数を返す

void CSUHeap::SetSRVNum(unsigned int srvNum){_srvNum = srvNum;} // SRV数セット
unsigned int CSUHeap::GetSRVNum()           {return _srvNum;} // SRV数を返す
void CSUHeap::SetUAVNum(unsigned int uavNum){_uavNum = uavNum;} // UAV数セット
unsigned int CSUHeap::GetUAVNum()           {return _uavNum;} // UAV数を返す

CSUHeap::CSUHeap(
    const Heap&                  heap,
    unsigned int                 cbvNum,
    unsigned int                 srvNum,
    unsigned int                 uavNum)
    : Heap(heap), _cbvNum(cbvNum), _srvNum(srvNum), _uavNum(uavNum){}