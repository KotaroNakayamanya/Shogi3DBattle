#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class KingVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // ‹â@’¸“_W‡ì¬
};