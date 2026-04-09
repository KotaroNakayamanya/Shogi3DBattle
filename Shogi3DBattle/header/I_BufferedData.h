#pragma once

#include"Buff.h"

class I_BufferedData
{
public:
    virtual HRESULT WriteToBuff(Buff * buff) = 0; // バッファに書き込む

    virtual unsigned int GetSize() = 0; // データサイズを返す

    virtual void         SetStartDataIdx(unsigned int idx) = 0; // データスタート位置セット
    virtual unsigned int GetStartDataIdx()                 = 0; // データスタート位置を返す

    virtual ~I_BufferedData() = default;
};