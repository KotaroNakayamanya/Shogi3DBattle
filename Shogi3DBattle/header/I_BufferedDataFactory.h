#pragma once

#include"I_BufferedData.h"
#include<memory>

class I_BufferedDataFactory
{
public:
    virtual std::unique_ptr<I_BufferedData> CreateUniquePtr() = 0; // バッファ書き込み用データ作成

    virtual ~I_BufferedDataFactory() = default;
};