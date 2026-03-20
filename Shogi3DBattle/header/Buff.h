#pragma once

#include<d3d12.h>
#include<wrl.h>

class Buff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
    enum BuffType
    {
        BACKBUFF, // バックバッファ
        DEPTH_STENCIL, // デプスステンシルバッファ
        VERTEX, // 頂点バッファ
        INDEX,  // インデックスバッファ
        CONSTANT, // コンスタントバッファ
        TEXTURE // テクスチャバッファ
    };

protected:
    ComPtr<ID3D12Resource> _buff; // バッファ

public:
    void SetBuff(ComPtr<ID3D12Resource> buff); // バッファセット
    ID3D12Resource* GetBuff();                 // バッファを返す

    Buff();
    ~Buff();
};