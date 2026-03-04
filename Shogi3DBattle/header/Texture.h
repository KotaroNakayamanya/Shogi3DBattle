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

    HRESULT CreateTextureDescHeap( // テクスチャディスクリプタヒープ作成
        ID3D12Device* device,
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc);

    void CreateSRV(
        ID3D12Device* device,
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc); // SRV作成

    
    HRESULT CreateTextureBuff( // テクスチャバッファ作成
        ID3D12Device* device,
        D3D12_HEAP_PROPERTIES heapProp,
        D3D12_RESOURCE_DESC   resourceDesc);

    HRESULT WriteTextureToBuff(); // テクスチャ書き込み

    

public:
    // テクスチャオブジェクト作成
    HRESULT CreateTextureObj(
        TextureArg::CreateTextureObjArg arg);
    // テクスチャディスクリプタヒープを渡す
    ID3D12DescriptorHeap* GetTextureDescHeap();

    Texture();
    ~Texture();
};