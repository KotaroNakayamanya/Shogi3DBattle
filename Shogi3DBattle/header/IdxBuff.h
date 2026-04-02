#pragma once

#include"Buff.h"
#include<memory>
#include"VertIndices.h"

class IdxBuff : public Buff
{
public:
    HRESULT WriteToIdxBuff(VertIndices* boardVertIndices, VertIndices* pieceVertIndices);  // インデックスに書き込み

    IdxBuff()  = default;
    ~IdxBuff() = default;
};