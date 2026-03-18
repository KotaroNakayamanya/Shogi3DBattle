#pragma once

#include<d3d12.h>
#include<wrl.h>

class BackBuff
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _backBuff; // バックバッファ
    D3D12_CPU_DESCRIPTOR_HANDLE _rtvHandle; // RTVハンドル

public:
    ID3D12Resource* GetBackBuff(); // バックバッファを返す
    D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle(); // RTVハンドルを返す

    BackBuff();
    ~BackBuff();
};