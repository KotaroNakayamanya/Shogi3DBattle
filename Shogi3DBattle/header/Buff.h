#pragma once

#include<d3d12.h>
#include<wrl.h>
#include"GameObj.h"

class Buff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
    enum BuffType
    {
        DEPTH_STENCIL, // デプスステンシルバッファ
        VERTEX, // 頂点バッファ
        INDEX,  // インデックスバッファ
        CONSTANT, // コンスタントバッファ
        TEXTURE, // テクスチャバッファ
        RENDER_TEX // レンダーテクスチャバッファ
    };

protected:
    ComPtr<ID3D12Resource> _buff; // バッファ

public:
    template<typename T>
    HRESULT WriteToBuff(std::vector<T> vec, unsigned int idx); // バッファへ書き込み

    D3D12_RESOURCE_DESC GetResourceDesc(); // リソースディスクリプタを返す

    void            SetBuff(ComPtr<ID3D12Resource> buff); // バッファセット
    ID3D12Resource* GetBuff();                            // バッファを返す

    virtual ~Buff() = default;
};

template HRESULT Buff::WriteToBuff<GameObj::Vert> (std::vector<GameObj::Vert> , unsigned int idx);
template HRESULT Buff::WriteToBuff<unsigned short>(std::vector<unsigned short>, unsigned int idx);