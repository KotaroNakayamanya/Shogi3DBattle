#pragma once

#include"VShader.h"
#include"PShader.h"
#include"VertBuff.h"
#include"IdxBuff.h"
#include"TexBuff.h"

class Device
{
    friend class DXGIFactory; // DXGIFactoryから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Device> _device; // Direct3Dデバイス

    D3D12_HEAP_PROPERTIES GetVertHeapProp(); // 頂点ヒーププロパティ
    D3D12_RESOURCE_DESC GetVertResourceDesc(UINT byteSize);  // 頂点リソースディスクリプタ
    D3D12_HEAP_PROPERTIES GetTexHeapProp();   // テクスチャヒーププロパティ
    D3D12_RESOURCE_DESC GetTexResourceDesc(); // テクスチャリソースディスクリプタ
    DXGI_SAMPLE_DESC GetSampleDesc(); // サンプリングディスクリプタ

public:
    HRESULT CreateVShader(VShader* vShaderObj); // 頂点シェーダーオブジェクト作成
    HRESULT CreatePShader(PShader* pShaderObj); // ピクセルシェーダーオブジェクト作成
    HRESULT CreateVertBuff(VertBuff* vertBuffObj, UINT byteSize); // 頂点バッファ作成
    HRESULT CreateIdxBuff (IdxBuff* idxBuffObj,   UINT byteSize); // インデックスバッファ作成
    HRESULT CreateTexBuff(TexBuff* texBuffObj); // テクスチャバッファオブジェクト作成

    ID3D12Device* GetDevice(); // Direct3Dデバイスを渡す

    Device();
    ~Device();
};