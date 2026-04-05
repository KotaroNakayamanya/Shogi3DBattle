#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class RookVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // ”ò@’¸“_W‡ì¬
};