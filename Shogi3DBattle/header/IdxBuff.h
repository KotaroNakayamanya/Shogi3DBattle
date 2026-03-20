#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<array>
#include<memory>
#include"Board.h"
#include"Piece.h"

class IdxBuff
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _idxBuff;  // インデックスバッファ

public:
    HRESULT WriteToIdxBuff(Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces);  // インデックスに書き込み
    D3D12_GPU_VIRTUAL_ADDRESS GetAddress(); // 頂点バッファアドレスを返す

    IdxBuff();
    ~IdxBuff();
};