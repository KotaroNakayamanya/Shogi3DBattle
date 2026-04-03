#pragma once

#include"Buff.h"
#include"Texture.h"

class TexBuff : public Buff
{
public:
    HRESULT WriteToTexBuff(Texture* tex); // テクスチャをバッファに書き込み
};