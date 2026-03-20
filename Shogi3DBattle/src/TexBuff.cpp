#include"TexBuff.h"

// テクスチャをバッファに書き込み
void TexBuff::WriteToTexBuff(Tex* tex)
{
    const auto& texture = tex->GetTex();

    _buff->WriteToSubresource(
        0,
        nullptr,
        texture.data(),
        sizeof(TexStruct::TexRGBA) * 256,
        sizeof(TexStruct::TexRGBA) * texture.size());
}

//ID3D12Resource* TexBuff::GetTexBuff(){return _texBuff.Get();} // バッファを渡す

TexBuff::TexBuff(){}
TexBuff::~TexBuff(){}