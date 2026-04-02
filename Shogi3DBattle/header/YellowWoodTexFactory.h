#pragma once

#include"ITexFactory.h"

class YellowWoodTexFactory : public ITexFactory
{
public:
    void CreateTex(std::unique_ptr<Tex> tex) override; // 黄色木材テクスチャ作成

    YellowWoodTexFactory () = default;
    ~YellowWoodTexFactory() = default;
};