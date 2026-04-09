#pragma once

#include"I_BufferedData.h"

class B_BufferedData : public I_BufferedData
{
protected:
    unsigned int _startDataIdx; // バッファ内のデータ書き込み位置

public:
    void         SetStartDataIdx(unsigned int idx) override; // データスタート位置セット
    unsigned int GetStartDataIdx()                 override; // データスタート位置を返す
};