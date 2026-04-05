#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class KnightVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // Œj@’¸“_W‡ì¬
};