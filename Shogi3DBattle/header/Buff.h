#pragma once

#include<d3d12.h>
#include<wrl.h>

class Buff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _buff; // バッファ

public:
    void SetBuff(ComPtr<ID3D12Resource> buff); // バッファセット
    ID3D12Resource* GetBuff(); // バッファを返す

    Buff();
    ~Buff();
};