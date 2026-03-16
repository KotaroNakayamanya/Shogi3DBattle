#pragma once

#include<d3d12.h>
#include<wrl.h>
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
    HRESULT WriteToIdxBuff(Board* board, Piece* piece);  // インデックスに書き込み
    //HRESULT WriteToIdxBuff(ShogiObj* shogiObj);  // インデックスに書き込み
    D3D12_GPU_VIRTUAL_ADDRESS GetAddress(); // 頂点バッファアドレスを返す

    IdxBuff();
    ~IdxBuff();
};