#pragma once

#include<d3d12.h>
#include<wrl.h>

class RTVHeap
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12DescriptorHeap> _rtvHeap; // RTVヒープ
    UINT _rtvOffset; // RTVオフセット数

public:
    // 引数の位置のRTVハンドルを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle(UINT i);

    RTVHeap();
    ~RTVHeap();
};