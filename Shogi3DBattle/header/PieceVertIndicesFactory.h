#pragma once

#include"I_BufferedDataFactory.h"

class PieceVertIndicesFactory : public I_BufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // 駒のインデックス集合作成
};