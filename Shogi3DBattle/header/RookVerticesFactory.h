#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class RookVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // ”ò@’¸“_W‡ì¬
};