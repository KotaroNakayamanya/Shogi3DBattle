#pragma once

#include"ITexFactory.h"

class YellowWoodTexFactory : public ITexFactory
{
public:
    std::unique_ptr<Texture> CreateTex() override; // 黄色木材テクスチャ作成
};