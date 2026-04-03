#pragma once

#include"IBufferedDataFactory.h"
#include"Texture.h"

class YellowWoodTexFactory : public IBufferedDataFactory<Pixel>
{
public:
    std::unique_ptr<BufferedData<Pixel>> CreateBufferedData() override; // 黄色木材テクスチャ作成
};