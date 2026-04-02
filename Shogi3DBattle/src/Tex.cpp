#include"Tex.h"

void Tex::SetPixels(std::vector<Tex::Pixel> pixels){_pixels = pixels;} // ピクセル集合セット
std::vector<Tex::Pixel> Tex::GetPixels(){return _pixels;} // ピクセル集合を返す
void Tex::SetWidth (UINT width) {_width  = width;}  // 横サイズセット
UINT Tex::GetWidth ()           {return _width;}    // 横サイズを返す
void Tex::SetHeight(UINT height){_height = height;} // 縦サイズセット
UINT Tex::GetHeight()           {return _height;}   // 縦サイズを返す

Tex::Tex(){}
Tex::~Tex(){}