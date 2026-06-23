#include"I_Texture.h"
#include<cassert>

// バッファに書き込み
void I_Texture::WriteToBuff(ID3D12Resource* buff)
{
    HRESULT result;
    result = buff->WriteToSubresource(
        0,
        nullptr,
        _pixels.data(),
        sizeof(Pixel) * GetWidth(),
        0);
    assert(SUCCEEDED(result));
}

void               I_Texture::SetPixels(std::vector<Pixel> pixels){_pixels = pixels;} // ピクセルセット
std::vector<Pixel> I_Texture::GetPixels()                         {return _pixels;}   // ピクセルを返す
void               I_Texture::SetWidth (UINT width)               {_width  = width;}  // 横サイズセット
UINT               I_Texture::GetWidth ()                         {return _width;}    // 横サイズを返す
void               I_Texture::SetHeight(UINT height)              {_height = height;} // 縦サイズセット
UINT               I_Texture::GetHeight()                         {return _height;}   // 縦サイズを返す

I_Texture::I_Texture()
{
    UINT lineSize = 256;
    _width  = lineSize;
    _height = lineSize;

    _pixels.resize(_width * _height);

    // 白色でクリア
    for (auto& pixel : _pixels)
    {
        pixel.r = 255;
        pixel.g = 255;
        pixel.b = 255;
        pixel.a = 255;
    }

}