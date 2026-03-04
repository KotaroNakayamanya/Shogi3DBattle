#include"Texture.h"

#include<vector>
#include<cassert>

#include "TextureStruct.h"

// テクスチャオブジェクト作成
HRESULT Texture::CreateTextureObj(
    TextureArg::CreateTextureObjArg arg)
{
    // テクスチャバッファ作成
    if(FAILED(CreateTextureBuff(
        arg.device, arg.heapProp, arg.resourceDesc)))
    {
        assert(false); return E_FAIL;
    }
    // テクスチャディスクリプタヒープ作成
    if (FAILED(CreateTextureDescHeap(
        arg.device, arg.heapDesc)))
    {
        assert(false); return E_FAIL;
    }
    // SRV作成
    CreateSRV(arg.device, arg.srvDesc);

    return S_OK;
}

// テクスチャバッファ作成
HRESULT Texture::CreateTextureBuff(
    ID3D12Device* device,
    D3D12_HEAP_PROPERTIES heapProp,
    D3D12_RESOURCE_DESC   resourceDesc)
{
    HRESULT result;

    // テクスチャバッファ作成
    result = device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, // テクスチャ
        nullptr,
        IID_PPV_ARGS(_textureBuff.ReleaseAndGetAddressOf()));
    if (FAILED(result))
    {
        assert(false); return result;
    }

    // テクスチャをバッファに書き込み
    result = WriteTextureToBuff();
    if (FAILED(result))
    {
        assert(false); return result;
    }

    return result;
}

// テクスチャ書き込み
HRESULT Texture::WriteTextureToBuff()
{
    std::vector<TextureStruct::TextureRGBA> pieceTextureData;
    pieceTextureData.resize(256*256);

    for (auto& texture : pieceTextureData)
    {
        // 216 178 128 でちょうどいい茶色
        texture.R = 216;
        texture.G = 178;
        texture.B = 128;     
        texture.A = 255;
    }

    return _textureBuff->WriteToSubresource(
        0,
        nullptr,
        pieceTextureData.data(),
        sizeof(TextureStruct::TextureRGBA)*256,
        sizeof(TextureStruct::TextureRGBA)*pieceTextureData.size());
}

// テクスチャディスクリプタヒープ作成
HRESULT Texture::CreateTextureDescHeap(
    ID3D12Device* device,
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc)
{
    return device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_textureDescHeap.ReleaseAndGetAddressOf()));
}

// SRV作成
void Texture::CreateSRV(
    ID3D12Device* device,
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc)
{
    device->CreateShaderResourceView(
        _textureBuff.Get(),
        &srvDesc,
        _textureDescHeap->GetCPUDescriptorHandleForHeapStart());
}



// テクスチャディスクリプタヒープを渡す
ID3D12DescriptorHeap* Texture::GetTextureDescHeap()
{
    return _textureDescHeap.Get();
}




Texture::Texture(){}
Texture::~Texture(){}