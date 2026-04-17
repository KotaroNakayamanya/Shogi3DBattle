#pragma once

#include"I_BufferedData.h"
#include<vector>
#include<cassert>

template<typename T>
class NaturalBufferedData : public I_BufferedData
{
protected:
    std::vector<T> _datas;        // バッファに書き込むデータ

public:
    // バッファに書き込み
    void WriteToBuff(ID3D12Resource* buff) override
    {
        T* buffMap;

        HRESULT result;
        result = buff->Map(0, nullptr, (void**)&buffMap);
        assert(SUCCEEDED(result));

        buffMap += _startDataIdx;

        std::copy(_datas.begin(), _datas.end(), buffMap);

        buff->Unmap(0, nullptr);
    }

    void           SetDatas(std::vector<T> datas){_datas = datas;} // データ集合セット
    std::vector<T> GetDatas()                    {return _datas;}  // データ集合を返す   
};