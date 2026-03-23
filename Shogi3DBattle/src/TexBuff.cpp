#include"TexBuff.h"

// テクスチャをバッファに書き込み
void TexBuff::WriteToTexBuff(Tex* tex)
{
    const auto& texture = tex->GetTex();

    _buff->WriteToSubresource(
        0,
        nullptr,
        texture.data(),
        sizeof(TexStruct::TexRGBA) * tex->GetWidth(),
        0);
}

TexBuff::TexBuff(){}
TexBuff::~TexBuff(){}