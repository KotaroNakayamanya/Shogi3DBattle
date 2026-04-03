#include"Texture.h"

void Texture::SetWidth (UINT width) {_width  = width;}  // 横サイズセット
UINT Texture::GetWidth ()           {return _width;}    // 横サイズを返す
void Texture::SetHeight(UINT height){_height = height;} // 縦サイズセット
UINT Texture::GetHeight()           {return _height;}   // 縦サイズを返す