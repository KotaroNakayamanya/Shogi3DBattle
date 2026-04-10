#include"I_Texture.h"
void               I_Texture::SetPixels(std::vector<Pixel> pixels){_pixels = pixels;}
std::vector<Pixel> I_Texture::GetPixels(){return _pixels;}

// バッファに書き込み
HRESULT I_Texture::WriteToBuff(Buff* buff)
{
    return buff->GetBuff()->WriteToSubresource(
        0,
        nullptr,
        _pixels.data(),
        sizeof(Pixel) * GetWidth(),
        0);
}

unsigned int I_Texture::GetSize()
{
    return 1;
}


void I_Texture::SetWidth (UINT width) {_width  = width;}  // 横サイズセット
UINT I_Texture::GetWidth ()           {return _width;}    // 横サイズを返す
void I_Texture::SetHeight(UINT height){_height = height;} // 縦サイズセット
UINT I_Texture::GetHeight()           {return _height;}   // 縦サイズを返す