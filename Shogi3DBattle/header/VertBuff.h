#pragma once

#include"Buff.h"
#include<memory>
#include"GameObj.h"


class VertBuff : public Buff
{
public:
    HRESULT WriteToBuff(GameObj* gameObj, UINT idx); // 頂点バッファに書き込み

    VertBuff();
    ~VertBuff();
};