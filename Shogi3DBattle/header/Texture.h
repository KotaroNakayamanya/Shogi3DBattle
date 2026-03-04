#pragma once

#include<d3d12.h>
#include<wrl.h>

#include"TextureArg.h"

class Texture
{
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _textureBuff; // テクスチャバッファ
    ComPtr<ID3D12DescriptorHeap> _textureDescHeap; // テクスチャディスクリプタヒープ

    HRESULT CreateTextureBuff(ID3D12Device* device, DXGI_SAMPLE_DESC sampleDesc); // テクスチャバッファ作成

    HRESULT WriteTextureToBuff(); // テクスチャ書き込み

    HRESULT CreateDescHeap(ID3D12Device* device); // テクスチャディスクリプタヒープ作成

    void CreateSRV(ID3D12Device* device); // SRV作成

    
    

    D3D12_RESOURCE_DESC GetResourceDesc();   // リソースディスクリプタ
    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(); // テクスチャヒープディスクリプタ
    D3D12_HEAP_PROPERTIES GetHeapProp(); // テクスチャヒーププロパティ
    D3D12_SHADER_RESOURCE_VIEW_DESC GetSRVDesc(); // SRVディスクリプタ

    

public:
    // テクスチャオブジェクト作成
    HRESULT CreateTextureObj(
        TextureArg::CreateTextureObjArg arg);
    // テクスチャディスクリプタヒープを渡す
    ID3D12DescriptorHeap* GetDescHeap();

    Texture();
    ~Texture();
};