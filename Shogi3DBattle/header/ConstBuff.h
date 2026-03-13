#pragma once

#include<d3d12.h>
#include<wrl.h>

class ConstBuff
{
    friend class Device; // Direct3Dから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _constBuff; // コンスタントバッファ

public:
    ID3D12Resource* GetBuff(); // バッファを返す

    ConstBuff();
    ~ConstBuff();
};