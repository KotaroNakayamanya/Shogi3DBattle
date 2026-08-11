#include"WhiteTexture.h"
#include"Application.h"

WhiteTexture::WhiteTexture()
{
    std::vector<Pixel> pixels;

    // サイズは256*256
    UINT lineSize = 256;
    UINT width    = lineSize;
    UINT height   = lineSize;
    pixels.resize(width * height);

    // 白色でクリア
    for (auto& pixel : pixels)
    {
        pixel.r = 255;
        pixel.g = 255;
        pixel.b = 255;
        pixel.a = 255;
    }

    SetPixels(pixels);
    SetWidth (width);
    SetHeight(height);
}
