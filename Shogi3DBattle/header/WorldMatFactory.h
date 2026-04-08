#pragma once

#include"IBufferedDataFactory.h"
#include<DirectXMath.h>

class WorldMatFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // ƒ[ƒ‹ƒhs—ñì¬
};