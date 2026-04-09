#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class BoardVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // ’¸“_W‡ì¬
};