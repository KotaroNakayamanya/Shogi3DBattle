#pragma once

#include<d3d12.h>
#include<wrl.h>

#include"TextureArgument.h"

class Texture
{
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _textureBuffer; // テクスチャバッファ
    ComPtr<ID3D12DescriptorHeap> _textureDescHeap; // テクスチャディスクリプタヒープ

    HRESULT CreateTextureDescHeap( // テクスチャディスクリプタヒープ作成
        ID3D12Device* device,
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc);

    void CreateSRV(
        ID3D12Device* device,
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc); // SRV作成

    
    HRESULT CreateTextureBuffer( // テクスチャバッファ作成
        ID3D12Device* device,
        D3D12_HEAP_PROPERTIES heapProperty,
        D3D12_RESOURCE_DESC   resourceDesc);

    HRESULT WriteTextureToBuffer(); // テクスチャ書き込み

    

public:
    // テクスチャオブジェクト作成
    HRESULT CreateTextureObject(
        TextureArgument::CreateTextureObjectArgument arg);
    // テクスチャディスクリプタヒープを渡す
    ID3D12DescriptorHeap* GetTextureDescriptorHeap();

    Texture();
    ~Texture();
};