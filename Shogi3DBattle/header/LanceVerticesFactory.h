#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class LanceVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // @’¸“_W‡ì¬
};