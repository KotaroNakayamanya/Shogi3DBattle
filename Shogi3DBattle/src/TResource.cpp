#include"TResource.h"
#include<vector>
#include"TextureStruct.h"

// テクスチャ書き込み
HRESULT TResource::WriteTextureToBuff(ID3D12Resource* tBuff)
{
    std::vector<TextureStruct::TextureRGBA> pieceTextureData;
    pieceTextureData.resize(256*256);

    UINT count = 0;
    for (auto& texture : pieceTextureData)
    {
        // 216 178 128 でちょうどいい茶色
        //texture.R = 216;
        //texture.G = 178;
        //texture.B = 128;     
        //texture.A = 255;

        UINT aaa = count % 256;

        texture.R = 216 * aaa / 256;
        texture.G = 178 * aaa / 256;
        texture.B = 128 * aaa / 256;     
        texture.A = 0;

        count ++;
    }
    
    return tBuff->WriteToSubresource(
        0,
        nullptr,
        pieceTextureData.data(),
        sizeof(TextureStruct::TextureRGBA)*256,
        sizeof(TextureStruct::TextureRGBA)*pieceTextureData.size());
}

TResource::TResource(){}
TResource::~TResource(){}