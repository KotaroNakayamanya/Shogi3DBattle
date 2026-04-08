#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class BishopVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // Šp@’¸“_W‡ì¬
};