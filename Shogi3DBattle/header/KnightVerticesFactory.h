#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class KnightVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // Œj@’¸“_W‡ì¬
};