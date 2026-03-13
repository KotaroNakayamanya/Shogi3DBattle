#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

class IdxBuff
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _idxBuff;  // インデックスバッファ

public:
    HRESULT WriteIdxBuff(std::vector<unsigned short> indexPtr);  // インデックスに書き込み
    ID3D12Resource* GetIdxBuff(); // インデックスバッファを返す

    IdxBuff();
    ~IdxBuff();
};