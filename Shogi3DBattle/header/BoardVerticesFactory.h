#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class BoardVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // ’¸“_W‡ì¬
};