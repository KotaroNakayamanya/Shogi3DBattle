#pragma once

#include<d3d12.h>

class I_BufferedData
{
protected:
    unsigned int _startDataIdx; // バッファ内のデータ書き込み位置

public:
    virtual void WriteToBuff(ID3D12Resource* buff) = 0; // バッファに書き込む

    void         SetStartDataIdx(unsigned int idx){_startDataIdx = idx;}  // データスタート位置セット
    unsigned int GetStartDataIdx()                {return _startDataIdx;} // データスタート位置を返す

    virtual ~I_BufferedData() = default;
};