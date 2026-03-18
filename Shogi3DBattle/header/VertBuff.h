#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<array>
#include<memory>
#include"Board.h"
#include"Piece.h"

class VertBuff
{
    friend class Device; // デバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _vertBuff; // 頂点バッファ

public:
    //HRESULT WriteToVertBuff(Board* board, Piece* piece); // 頂点バッファに書き込み
    HRESULT WriteToVertBuff(Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces); // 頂点バッファに書き込み
    //HRESULT WriteToVertBuff(ShogiObj* shogiObj); // 頂点バッファに書き込み
    D3D12_GPU_VIRTUAL_ADDRESS GetAddress(); // 頂点バッファアドレスを返す

    ID3D12Resource* GetVertBuff(); // 頂点バッファを返す

    VertBuff();
    ~VertBuff();
};