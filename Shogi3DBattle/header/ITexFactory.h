#pragma once

#include"Tex.h"
#include<memory>

class ITexFactory
{
public:
    virtual void CreateTex(std::unique_ptr<Tex> tex) = 0; // テクスチャ作成

    ITexFactory         () = default;
    virtual ~ITexFactory() = default;
};