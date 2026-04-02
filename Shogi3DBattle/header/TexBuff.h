#pragma once

#include"Buff.h"
#include"Tex.h"

class TexBuff : public Buff
{
public:
    HRESULT WriteToTexBuff(Tex* tex); // テクスチャをバッファに書き込み

    TexBuff () = default;
    ~TexBuff() = default;
};