#pragma once

#include"BufferedData.h"

template<typename T>
class NaturalBufferedData : public BufferedData<T>
{
private:
    std::vector<T> _datas;        // バッファに書き込むデータ

public:
    void           SetDatas(std::vector<T> datas) override {_datas = datas;}       // データ集合セット
    std::vector<T> GetDatas()                     override {return _datas;}        // データ集合を返す
};