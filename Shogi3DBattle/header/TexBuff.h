#pragma once

#include"Buff.h"
#include"Tex.h"

class TexBuff : public Buff
{
public:
    void WriteToTexBuff(Tex* tex); // テクスチャをバッファに書き込み

    TexBuff();
    ~TexBuff();
};