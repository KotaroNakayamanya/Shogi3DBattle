#pragma once

#include"Buff.h"

class BufferedData
{
protected:
    unsigned int   _startDataIdx; // バッファ内のデータ書き込みスタート位置

public:
    // バッファに書き込む
    virtual HRESULT WriteToBuff(Buff* buff) = 0;

    void         SetStartDataIdx(unsigned int idx){_startDataIdx = idx;}  // データスタート位置セット
    unsigned int GetStartDataIdx()                {return _startDataIdx;} // データスタート位置セット

    virtual unsigned int GetSize() = 0;

    virtual ~BufferedData() = default;
};