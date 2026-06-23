#include"WoodTexture.h"

WoodTexture::WoodTexture(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int lineSize = 256;
    unsigned int width  = lineSize;
    unsigned int height = lineSize;

    std::vector<Pixel> pixels;
    pixels.resize(width * height);

    // 基本色を入れる
    for (auto& pixel : pixels)
    {
        //pixel.r = 226;
        //pixel.g = 232;
        //pixel.b =  75;
        pixel.r = r;
        pixel.g = g;
        pixel.b = b;
        pixel.a = 255;
    }

    // 板目を入れる
    UINT x = 0;
    UINT y = 0;
    auto subtRate = 0.07f;
    for (auto& pixel : pixels)
    {
        if ((x+y) % 20 == 1)
        {
            pixel.r -= static_cast<unsigned char>(pixel.r * subtRate);
            pixel.g -= static_cast<unsigned char>(pixel.g * subtRate);
            pixel.b -= static_cast<unsigned char>(pixel.b * subtRate);
        }

        // xとyの次の座標を取得
        x++;            // xを足す
        if (x >= width) // xが端を超えたらyを足してxを0に戻す
        {
            y++;
            x = 0;
        }
    }
    SetPixels(pixels);
    SetWidth(width);
    SetHeight(height);
}