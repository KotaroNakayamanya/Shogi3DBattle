#pragma once

#include"I_BufferedData.h"
#include<vector>

template<typename T>
class I_NaturalBufferedData : public I_BufferedData
{
protected:
    std::vector<T> _datas;        // バッファに書き込むデータ

public:
    // バッファに書き込み
    HRESULT WriteToBuff(Buff* buff) override
    {
        T* buffMap;

        HRESULT result = buff->GetBuff()->Map(0, nullptr, (void**)&buffMap);
        if (FAILED(result)) return result;

        buffMap += _startDataIdx;

        std::copy(_datas.begin(), _datas.end(), buffMap);

        buff->GetBuff()->Unmap(0, nullptr);

        return S_OK;
    }

    unsigned int GetSize() override {return _datas.size(); }

    void SetDatas(std::vector<T> datas){_datas = datas;} // データ集合セット
};