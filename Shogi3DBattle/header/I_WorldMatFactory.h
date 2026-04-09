#pragma once

#include"WorldMat.h"
#include<memory>

class I_WorldMatFactory
{
public:
    virtual std::unique_ptr<WorldMat> CreateWorldMat() = 0; // ƒ[ƒ‹ƒhs—ñì¬

    virtual ~I_WorldMatFactory() = default;
};