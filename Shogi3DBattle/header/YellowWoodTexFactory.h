#pragma once

#include"I_BufferedDataFactory.h"

class YellowWoodTexFactory : public I_BufferedDataFactory
{
public:
    std::unique_ptr<I_BufferedData> CreateUniquePtr() override; // 黄色木材テクスチャ作成
};