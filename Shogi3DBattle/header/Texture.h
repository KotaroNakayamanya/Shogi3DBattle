#pragma once

#include"NaturalBufferedData.h"
#include<d3d12.h>

struct Pixel
{
    unsigned char r, g, b, a;
};

class Texture : public NaturalBufferedData<Pixel>
{
private:
    UINT _width;  // 横サイズ
    UINT _height; // 縦サイズ

public:
    void SetWidth(UINT width);   // 横サイズセット
    UINT GetWidth();             // 横サイズを返す
    void SetHeight(UINT height); // 縦サイズセット
    UINT GetHeight();            // 縦サイズを返す
};