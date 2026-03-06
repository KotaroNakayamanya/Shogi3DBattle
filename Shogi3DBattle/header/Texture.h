#pragma once

#include<d3d12.h>
#include<wrl.h>

#include"TextureArg.h"

class Texture
{
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _buff; // テクスチャバッファ

    HRESULT CreateTextureBuff( // テクスチャバッファ作成
        TextureArg::CreateTextureObjArg arg);
    HRESULT WriteTextureToBuff(); // テクスチャ書き込み
    
    D3D12_RESOURCE_DESC GetResourceDesc(DXGI_SAMPLE_DESC sampleDesc);   // リソースディスクリプタ
    D3D12_HEAP_PROPERTIES GetHeapProp(); // テクスチャヒーププロパティ


public:
    HRESULT CreateTextureObj( // テクスチャオブジェクト作成
        TextureArg::CreateTextureObjArg arg);

    ID3D12Resource* GetBuff(); // バッファを返す

    Texture();
    ~Texture();
};