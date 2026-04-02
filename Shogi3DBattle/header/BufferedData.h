#pragma once

#include<vector>

template <typename T>
class BufferedData
{
private:
    //std::vector<T> _datas;        // バッファに書き込むデータ
    unsigned int   _startDataIdx; // バッファ内のデータ書き込みスタート位置

public:
    //void           SetDatas       (std::vector<T> datas){_datas = datas;}       // データ集合セット
    //std::vector<T> GetDatas       ()                    {return _datas;}        // データ集合を返す
    virtual void           SetDatas(std::vector<T> datas) = 0; // データ集合セット
    virtual std::vector<T> GetDatas()                     = 0; // データ集合を返す

    void           SetStartDataIdx(unsigned int idx)    {_startDataIdx = idx;}  // データスタート位置セット
    unsigned int   GetStartDataIdx()                    {return _startDataIdx;} // データスタート位置セット

    virtual ~BufferedData() = default;
};