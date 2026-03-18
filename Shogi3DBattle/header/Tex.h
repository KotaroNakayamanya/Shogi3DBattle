#pragma once

#include"TexStruct.h"
#include<array>

class Tex
{
private:
    std::array<TexStruct::TexRGBA, 256*256> _tex;

public:
    void SetTex(std::array<TexStruct::TexRGBA, 256*256> tex); // テクスチャセット
    std::array<TexStruct::TexRGBA, 256*256> GetTex();         // テクスチャを返す

    Tex();
    ~Tex();
};