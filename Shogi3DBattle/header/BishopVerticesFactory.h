#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class BishopVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // Šp@’¸“_W‡ì¬
};