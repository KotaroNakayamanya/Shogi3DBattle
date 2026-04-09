#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class BishopVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // Šp@’¸“_W‡ì¬
};