#pragma once

#include"Buff.h"
#include<array>
#include<memory>
#include"Board.h"
#include"Piece.h"

class VertBuff : public Buff
{
public:
    // 頂点バッファに書き込み
    HRESULT WriteToVertBuff(Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces);
    // 頂点バッファアドレスを返す
    D3D12_GPU_VIRTUAL_ADDRESS GetAddress();

    VertBuff();
    ~VertBuff();
};