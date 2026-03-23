#include"Tex.h"

void Tex::SetTex(std::vector<TexStruct::TexRGBA> tex){_tex = tex;} // テクスチャセット
std::vector<TexStruct::TexRGBA> Tex::GetTex(){return _tex;} // テクスチャを返す
void Tex::SetWidth (UINT width) {_width  = width;}  // 横サイズセット
UINT Tex::GetWidth ()           {return _width;}    // 横サイズを返す
void Tex::SetHeight(UINT height){_height = height;} // 縦サイズセット
UINT Tex::GetHeight()           {return _height;}   // 縦サイズを返す

Tex::Tex(){}
Tex::~Tex(){}