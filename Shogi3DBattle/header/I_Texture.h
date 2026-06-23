#pragma once

#include"I_BufferedData.h"
#include"Pixel.h"
#include<d3d12.h>
#include<vector>

class I_Texture : public I_BufferedData
{
private:
    std::vector<Pixel> _pixels;
    UINT _width;  // 横サイズ
    UINT _height; // 縦サイズ

public:
    // バッファに書き込む
    void WriteToBuff(ID3D12Resource* buff) override;

    void               SetPixels(std::vector<Pixel> pixels); // ピクセルセット
    std::vector<Pixel> GetPixels();                          // ピクセルを返す
    void               SetWidth(UINT width);                 // 横サイズセット
    UINT               GetWidth();                           // 横サイズを返す
    void               SetHeight(UINT height);               // 縦サイズセット
    UINT               GetHeight();                          // 縦サイズを返す

    I_Texture();
    virtual ~I_Texture() = default;
};