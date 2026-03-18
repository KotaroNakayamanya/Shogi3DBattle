#include"Tex.h"

// テクスチャを返す
std::array<TexStruct::TexRGBA, 256*256> Tex::GetTex(){return _tex;}
// テクスチャセット
void Tex::SetTex(std::array<TexStruct::TexRGBA, 256*256> tex){_tex = tex;}

Tex::Tex(){}
Tex::~Tex(){}