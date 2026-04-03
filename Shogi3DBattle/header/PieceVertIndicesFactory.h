#pragma once

#include"IBufferedDataFactory.h"

class PieceVertIndicesFactory : public IBufferedDataFactory<unsigned short>
{
public:
    std::unique_ptr<BufferedData<unsigned short>> CreateBufferedData() override; // 駒のインデックス集合作成
};