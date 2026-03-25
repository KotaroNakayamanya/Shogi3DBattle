#pragma once

#include"VertIndices.h"

class IVertIndicesFactory
{
public:
    // 頂点インデックス集合作成
    virtual void CreateVertIndices(VertIndices* vertIndices) = 0;

    IVertIndicesFactory() = default;
    ~IVertIndicesFactory(){}
};