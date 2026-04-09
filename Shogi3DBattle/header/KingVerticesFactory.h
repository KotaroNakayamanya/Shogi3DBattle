#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class KingVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // ‰¤@’¸“_W‡ì¬
};