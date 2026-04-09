#pragma once

#include"I_BufferedData.h"

class B_BufferedData : public I_BufferedData
{
protected:
    unsigned int startIdxData; // バッファ内のデータ書き込み位置

public:
    virtual HRESULT WriteToBuff(Buff* buff) = 0; // バッファに書き込む
    virtual unsigned int GetSize() = 0; // データサイズを返す

    void         SetStartDataIdx(unsigned int idx){_startDataIdx = idx;}  // データスタート位置セット
    unsigned int GetStartDataIdx()                {return _startDataIdx;} // データスタート位置を返す
};