#pragma once

#include"IBufferedDataFactory.h"
#include"Texture.h"

class YellowWoodTexFactory : public IBufferedDataFactory
{
public:
    std::unique_ptr<BufferedData> CreateUniquePtr() override; // 黄色木材テクスチャ作成
};