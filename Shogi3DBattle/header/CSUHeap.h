#pragma once

#include<d3d12.h>
#include<wrl.h>

class CSUHeap
{
    friend class Device; // Direct3Dから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12DescriptorHeap> _csuHeap; // CBV,SRV,UAVヒープ
    UINT _descOffset; // ディスクリプタオフセット

    UINT _cbvNum; // CBV数
    UINT _srvNum; // SRV数
    UINT _uavNum; // UAV数
   
public:
    // 指定された位置のGPUディスクリプタハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetDescHandle(UINT i);
    // ヒープを返す
    ID3D12DescriptorHeap* GetCSUHeap();

    CSUHeap();
    ~CSUHeap();
};