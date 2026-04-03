#pragma once

#include"Texture.h"
#include<memory>

class ITexFactory
{
public:
    virtual std::unique_ptr<Texture> CreateTex() = 0; // テクスチャ作成

    virtual ~ITexFactory() = default;
};