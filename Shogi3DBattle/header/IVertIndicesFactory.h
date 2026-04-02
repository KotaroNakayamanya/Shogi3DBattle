#pragma once

#include"BufferedData.h"

class IVertIndicesFactory
{
public:
    // 頂点インデックス集合作成
    virtual void CreateVertIndices(BufferedData<unsigned short>* bufferedData) = 0;

    virtual ~IVertIndicesFactory() = default;
};