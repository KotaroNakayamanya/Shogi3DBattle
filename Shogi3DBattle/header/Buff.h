#pragma once

#include<d3d12.h>
#include<wrl.h>
#include"GameObj.h"
#include"Texture.h"
#include<type_traits>

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
    D3D12_GPU_VIRTUAL_ADDRESS GetStartAddress(); // バッファのスタート位置アドレスを返す

    template<typename T>
    HRESULT WriteToBuff(BufferedData<T>* bufferedData); // バッファへ書き込み

    D3D12_RESOURCE_DESC GetResourceDesc(); // リソースディスクリプタを返す

    void            SetBuff(ComPtr<ID3D12Resource> buff); // バッファセット
    ID3D12Resource* GetBuff();                            // バッファを返す

    virtual ~Buff() = default;
};

// バッファへ書き込み
template<typename T>
HRESULT Buff::WriteToBuff(BufferedData<T>* bufferedData)
{
    if (std::is_base_of<Pixel, T>::value) // テクスチャならWriteToSubresourceを使う
    {
        Texture* texture = dynamic_cast<Texture*>(bufferedData); // ポインタをアップキャスト

        return _buff->WriteToSubresource(
            0,
            nullptr,
            texture->GetDatas().data(),
            sizeof(Pixel) * texture->GetWidth(),
            0);
    }

    T* buffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&buffMap);
    if (FAILED(result)) return result;

    buffMap += bufferedData->GetStartDataIdx();
    std::vector<T> datas = bufferedData->GetDatas();

    std::copy(datas.begin(), datas.end(), buffMap);

    _buff->Unmap(0, nullptr);

    return S_OK;
}