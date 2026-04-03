#pragma once

#include"BufferedData.h"
#include<memory>

template<typename T>
class IBufferedDataFactory
{
public:
    virtual std::unique_ptr<BufferedData<T>> CreateBufferedData() = 0; // バッファ書き込み用データ作成

    virtual ~IBufferedDataFactory() = default;
};