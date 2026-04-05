#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class GoldVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // ‹à@’¸“_W‡ì¬
};