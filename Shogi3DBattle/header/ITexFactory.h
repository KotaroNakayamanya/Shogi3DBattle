#pragma once

#include"Texture.h"
#include<memory>

class ITexFactory
{
public:
    virtual void CreateTex(std::unique_ptr<Texture> tex) = 0; // テクスチャ作成

    ITexFactory         () = default;
    virtual ~ITexFactory() = default;
};