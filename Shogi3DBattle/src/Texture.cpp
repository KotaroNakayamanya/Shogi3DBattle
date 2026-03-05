#include"Texture.h"

#include<vector>
#include<cassert>

#include "TextureStruct.h"

// テクスチャオブジェクト作成
HRESULT Texture::CreateTextureObj(TextureArg::CreateTextureObjArg arg)
{
    // テクスチャバッファ作成
    if(FAILED(CreateTextureBuff(arg.device, arg.sampleDesc)))
    {
        assert(false); return E_FAIL;
    }
    // テクスチャ書き込み
    if (FAILED(WriteTextureToBuff()))
    {
        assert(false); return E_FAIL;
    }

    return S_OK;
}

// テクスチャバッファ作成
HRESULT Texture::CreateTextureBuff(ID3D12Device* device, DXGI_SAMPLE_DESC sampleDesc)
{
    D3D12_HEAP_PROPERTIES heapProp = GetHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetResourceDesc();

    resourceDesc.SampleDesc = sampleDesc;
 
    return device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, // テクスチャ
        nullptr,
        IID_PPV_ARGS(_buff.ReleaseAndGetAddressOf()));
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

    return _buff->WriteToSubresource(
        0,
        nullptr,
        pieceTextureData.data(),
        sizeof(TextureStruct::TextureRGBA)*256,
        sizeof(TextureStruct::TextureRGBA)*pieceTextureData.size());
}




// テクスチャヒーププロパティ
D3D12_HEAP_PROPERTIES Texture::GetHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_CUSTOM;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    prop.MemoryPoolPreference = // 転送L0
        D3D12_MEMORY_POOL_L0;
    prop.CreationNodeMask =
        0;
    prop.VisibleNodeMask =
        0;

    return prop;
}

// テクスチャリソースディスクリプタ
D3D12_RESOURCE_DESC Texture::GetResourceDesc()
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    desc.Height =
        256;
    desc.Width =
        256;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;  
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_UNKNOWN;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
   

    return desc;
}




// バッファを渡す
ID3D12Resource* Texture::GetBuff()
{
    return _buff.Get();
}




Texture::Texture(){}
Texture::~Texture(){}