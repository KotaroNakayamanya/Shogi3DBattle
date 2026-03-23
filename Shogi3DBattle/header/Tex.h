#pragma once

#include<d3d12.h>
#include"TexStruct.h"
#include<vector>

class Tex
{
private:
    std::vector<TexStruct::TexRGBA> _tex; // テクスチャ
    UINT _width;  // 横サイズ
    UINT _height; // 縦サイズ

public:
    void SetTex(std::vector<TexStruct::TexRGBA> tex); // テクスチャセット
    std::vector<TexStruct::TexRGBA> GetTex();         // テクスチャを返す
    void SetWidth(UINT width);   // 横サイズセット
    UINT GetWidth();             // 横サイズを返す
    void SetHeight(UINT height); // 縦サイズセット
    UINT GetHeight();            // 縦サイズを返す

    Tex();
    ~Tex();
};