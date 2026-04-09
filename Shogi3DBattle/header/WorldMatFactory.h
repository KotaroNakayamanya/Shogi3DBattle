#pragma once

#include"I_WorldMatFactory.h"

class WorldMatFactory : public I_WorldMatFactory
{
public:
    std::unique_ptr<I_WorldMat> CreateWorldMat() override; // ƒ[ƒ‹ƒhs—ñì¬
};