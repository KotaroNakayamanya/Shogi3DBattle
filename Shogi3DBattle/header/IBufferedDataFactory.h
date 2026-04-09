#pragma once

#include"I_BufferedData.h"
#include<memory>

class IBufferedDataFactory
{
public:
    virtual std::unique_ptr<I_BufferedData> CreateUniquePtr() = 0; // バッファ書き込み用データ作成

    virtual ~IBufferedDataFactory() = default;
};