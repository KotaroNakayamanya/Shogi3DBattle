#pragma once

#include<d3d12.h>
#include<wrl.h>

#include"TextureArg.h"

class TexBuff
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _texBuff; // テクスチャバッファ
    
    D3D12_RESOURCE_DESC GetResourceDesc(DXGI_SAMPLE_DESC sampleDesc);   // リソースディスクリプタ
    D3D12_HEAP_PROPERTIES GetHeapProp(); // テクスチャヒーププロパティ


public:
    HRESULT CreateTexBuffObj( // テクスチャバッファオブジェクト作成
        TextureArg::CreateTextureObjArg arg);

    ID3D12Resource* GetTexBuff(); // テクスチャバッファを返す

    TexBuff();
    ~TexBuff();
};