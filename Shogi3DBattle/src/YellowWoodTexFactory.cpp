#include"YellowWoodTexFactory.h"

// 黄色木材テクスチャ作成
std::unique_ptr<BufferedData<Pixel>> YellowWoodTexFactory::CreateBufferedData()
{
    std::unique_ptr<Texture> tex = std::make_unique<Texture>();

    unsigned int lineSize = 256;
    unsigned int width  = lineSize;
    unsigned int height = lineSize;

    std::vector<Pixel> pixels;
    pixels.resize(width * height);

    // 基本色を入れる
    for (auto& pixel : pixels)
    {
        pixel.r = 226;
        pixel.g = 232;
        pixel.b =  75;
        pixel.a = 255;
    }

    // 板目を入れる
    UINT x = 0;
    UINT y = 0;
    UINT subtColor = 10;
    for (auto& pixel : pixels)
    {
        if ((x+y) % 20 == 0)
        {
            pixel.r -= subtColor;
            pixel.g -= subtColor;
            pixel.b -= subtColor;

        }

        // xとyの次の座標を取得
        x++;            // xを足す
        if (x >= width) // xが端を超えたらyを足してxを0に戻す
        {
            y++;
            x = 0;
        }
    }

    tex->SetWidth (width);
    tex->SetHeight(height);
    tex->SetDatas(pixels);

    return tex;    
}