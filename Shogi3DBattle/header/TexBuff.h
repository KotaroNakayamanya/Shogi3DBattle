#pragma once

#include<d3d12.h>
#include<wrl.h>

class TexBuff
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _texBuff; // テクスチャバッファ

public:
    ID3D12Resource* GetTexBuff(); // テクスチャバッファを返す

    TexBuff();
    ~TexBuff();
};