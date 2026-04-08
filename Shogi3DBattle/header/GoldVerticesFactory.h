#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class GoldVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // ‹à@’¸“_W‡ì¬
};