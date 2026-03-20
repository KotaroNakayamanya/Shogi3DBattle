#pragma once

#include"Buff.h"
#include<memory>
#include"Board.h"
#include"Piece.h"

class IdxBuff : public Buff
{
public:
    HRESULT WriteToIdxBuff(Board* board, std::vector<std::unique_ptr<Piece>>& pieces);  // インデックスに書き込み

    IdxBuff();
    ~IdxBuff();
};