#pragma once

#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class PawnVerticesFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // â§Å@í∏ì_èWçáçÏê¨
};