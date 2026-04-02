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
    //HRESULT WriteToBuff(std::vector<T> vec, unsigned int idx); // バッファへ書き込み
    HRESULT WriteToBuff(BufferedData<T>* bufferedData, unsigned int idx); // バッファへ書き込み

    D3D12_RESOURCE_DESC GetResourceDesc(); // リソースディスクリプタを返す

    void            SetBuff(ComPtr<ID3D12Resource> buff); // バッファセット
    ID3D12Resource* GetBuff();                            // バッファを返す

    virtual ~Buff() = default;
};
//
//// バッファへ書き込み
//template<typename T>
//HRESULT Buff::WriteToBuff(std::vector<T> vec, unsigned int idx)
//{
//    T* buffMap;
//
//    HRESULT result = _buff->Map(0, nullptr, (void**)&buffMap);
//    if (FAILED(result)) return result;
//
//    buffMap += idx;
//
//    std::copy(vec.begin(), vec.end(), buffMap);
//
//    _buff->Unmap(0, nullptr);
//}

// バッファへ書き込み
template<typename T>
HRESULT Buff::WriteToBuff(BufferedData<T>* bufferedData, unsigned int idx)
{
    T* buffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&buffMap);
    if (FAILED(result)) return result;

    buffMap += idx;
    std::vector<T> datas = bufferedData->GetDatas();

    std::copy(datas.begin(), datas.end(), buffMap);

    _buff->Unmap(0, nullptr);
}