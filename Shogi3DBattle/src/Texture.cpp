#include"Texture.h"

void Texture::SetPixels(std::vector<Texture::Pixel> pixels){_pixels = pixels;} // ピクセル集合セット
std::vector<Texture::Pixel> Texture::GetPixels(){return _pixels;} // ピクセル集合を返す
void Texture::SetWidth (UINT width) {_width  = width;}  // 横サイズセット
UINT Texture::GetWidth ()           {return _width;}    // 横サイズを返す
void Texture::SetHeight(UINT height){_height = height;} // 縦サイズセット
UINT Texture::GetHeight()           {return _height;}   // 縦サイズを返す