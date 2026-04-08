#include"Texture.h"
void               Texture::SetPixels(std::vector<Pixel> pixels){_pixels = pixels;}
std::vector<Pixel> Texture::GetPixels(){return _pixels;}

// バッファに書き込み
HRESULT Texture::WriteToBuff(Buff* buff)
{
    return buff->GetBuff()->WriteToSubresource(
        0,
        nullptr,
        _pixels.data(),
        sizeof(Pixel) * GetWidth(),
        0);
}

unsigned int Texture::GetSize()
{
    return 1;
}


void Texture::SetWidth (UINT width) {_width  = width;}  // 横サイズセット
UINT Texture::GetWidth ()           {return _width;}    // 横サイズを返す
void Texture::SetHeight(UINT height){_height = height;} // 縦サイズセット
UINT Texture::GetHeight()           {return _height;}   // 縦サイズを返す