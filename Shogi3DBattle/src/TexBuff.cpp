#include"TexBuff.h"

// テクスチャをバッファに書き込み
HRESULT TexBuff::WriteToTexBuff(Tex* tex)
{
    const auto& texture = tex->GetTex();

    return _buff->WriteToSubresource(
        0,
        nullptr,
        texture.data(),
        sizeof(TexStruct::TexRGBA) * tex->GetWidth(),
        0);
}