#pragma once

#include<d3d12.h>
#include<wrl.h>

class DSVHeap
{
    friend class Device; // Direct3Dから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12DescriptorHeap> _dsvHeap; // DSVヒープ

public:
    DSVHeap(){}
    ~DSVHeap(){}
};