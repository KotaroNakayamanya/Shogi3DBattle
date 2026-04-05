#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class PawnVerticesFactory : public IBufferedDataFactory<Vert>
{
public:
    std::unique_ptr<BufferedData<Vert>> CreateUniquePtr() override; // â§Å@í∏ì_èWçáçÏê¨
};