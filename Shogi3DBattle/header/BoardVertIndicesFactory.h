#pragma once

#include"IBufferedDataFactory.h"

class BoardVertIndicesFactory : public IBufferedDataFactory<unsigned short>
{
public:
    std::unique_ptr<BufferedData<unsigned short>> CreateBufferedData() override; // 将棋盤インデックス集合作成
};