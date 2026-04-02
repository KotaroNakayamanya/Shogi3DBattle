#pragma once

#include"NaturalBufferedData.h"

class IVertIndicesFactory
{
public:
    // 頂点インデックス集合作成
    virtual void CreateVertIndices(NaturalBufferedData<unsigned short>* bufferedData) = 0;

    virtual ~IVertIndicesFactory() = default;
};