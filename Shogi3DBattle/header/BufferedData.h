#pragma once

#include<vector>

template <typename T>
class BufferedData
{
private:
    unsigned int   _startDataIdx; // バッファ内のデータ書き込みスタート位置

public:
    void                   SetStartDataIdx(unsigned int idx){_startDataIdx = idx;}  // データスタート位置セット
    unsigned int           GetStartDataIdx()                {return _startDataIdx;} // データスタート位置セット

    virtual std::vector<T> GetDatas()                       = 0; // データ集合を返す

    virtual ~BufferedData() = default;
};