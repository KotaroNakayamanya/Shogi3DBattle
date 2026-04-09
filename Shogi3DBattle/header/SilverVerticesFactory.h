#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class SilverVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // ‹â@’¸“_W‡ì¬
};