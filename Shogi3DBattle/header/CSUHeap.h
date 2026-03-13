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
   
public:
    ID3D12DescriptorHeap* GetCSUHeap(); // ヒープを渡す

    CSUHeap();
    ~CSUHeap();
};