#pragma once

#include"IBufferedDataFactory.h"
#include<DirectXMath.h>
#include"I_WorldMatFactory.h"

class WorldMatFactory : public IBufferedDataFactory, public I_WorldMatFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // ワールド行列作成
    std::unique_ptr<I_WorldMat> CreateWorldMat() override; // ワールド行列作成
};