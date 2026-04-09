#pragma once

#include"IBufferedDataFactory.h"

class PieceVertIndicesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // 駒のインデックス集合作成
};