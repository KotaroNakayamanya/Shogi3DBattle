#pragma once

#include"I_BufferedDataFactory.h"

class BoardVertIndicesFactory : public I_BufferedDataFactory
{
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // 将棋盤インデックス集合作成
};