#pragma once

#include"BufferedData.h"
#include<d3d12.h>
#include<vector>

struct Pixel
{
    unsigned char r, g, b, a;
};

class Texture : public BufferedData
{
private:
    std::vector<Pixel> _pixels;
    UINT _width;  // 横サイズ
    UINT _height; // 縦サイズ

public:
    void               SetPixels(std::vector<Pixel> pixels);
    std::vector<Pixel> GetPixels();
    // バッファに書き込む
    HRESULT WriteToBuff(Buff* buff) override;
    unsigned int GetSize() override;


    void SetWidth(UINT width);   // 横サイズセット
    UINT GetWidth();             // 横サイズを返す
    void SetHeight(UINT height); // 縦サイズセット
    UINT GetHeight();            // 縦サイズを返す
};