#pragma once

#include"BufferedData.h"
#include<d3d12.h>

struct Pixel
{
    unsigned char r, g, b, a;
};

class Texture : public BufferedData<Pixel>
{
public:
    

private:
    std::vector<Pixel> _pixels; // ピクセル集合
    UINT _width;  // 横サイズ
    UINT _height; // 縦サイズ

public:
    std::vector<Pixel> GetDatas() override; // データ集合を返す

    void SetPixels(std::vector<Pixel> tex); // ピクセル集合セット
    //std::vector<Pixel> GetPixels();         // ピクセル集合を返す
    void SetWidth(UINT width);   // 横サイズセット
    UINT GetWidth();             // 横サイズを返す
    void SetHeight(UINT height); // 縦サイズセット
    UINT GetHeight();            // 縦サイズを返す
};