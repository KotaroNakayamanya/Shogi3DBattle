#include"TexBuff.h"

// テクスチャをバッファに書き込み
HRESULT TexBuff::WriteToTexBuff(Tex* tex)
{
    //const auto& texture = tex->GetTex();
    const auto& texture = tex->GetPixels();

    return _buff->WriteToSubresource(
        0,
        nullptr,
        texture.data(),
        sizeof(Tex::Pixel) * tex->GetWidth(),
        0);
}