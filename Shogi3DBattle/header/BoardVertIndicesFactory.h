#pragma once

#include"IBufferedDataFactory.h"

class BoardVertIndicesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // 将棋盤インデックス集合作成
};