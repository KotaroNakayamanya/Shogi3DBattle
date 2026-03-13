#pragma once

#include"VShader.h"
#include"PShader.h"
#include"VertBuff.h"
#include"IdxBuff.h"
#include"TexBuff.h"
#include"ConstBuff.h"
#include"CSUHeap.h"
#include"CBV.h"
#include"SRV.h"

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
    D3D12_HEAP_PROPERTIES GetConstHeapProp(); // コンスタントヒーププロパティ
    D3D12_RESOURCE_DESC GetConstResourceDesc(UINT byteSize); // コンスタントリソースディスクリプタ

    D3D12_DESCRIPTOR_HEAP_DESC GetCSUHeapDesc(); // CSUヒープディスクリプタ

    D3D12_CONSTANT_BUFFER_VIEW_DESC GetCBVDesc(ID3D12Resource* cbvBuff); // CBVディスクリプタ
    D3D12_SHADER_RESOURCE_VIEW_DESC GetSRVDesc(); // SRVディスクリプタ

public:
    HRESULT CreateVShader(VShader* vShaderObj); // 頂点シェーダーオブジェクト作成
    HRESULT CreatePShader(PShader* pShaderObj); // ピクセルシェーダーオブジェクト作成
    HRESULT CreateVertBuff(VertBuff* vertBuffObj, UINT byteSize); // 頂点バッファ作成
    HRESULT CreateIdxBuff (IdxBuff* idxBuffObj,   UINT byteSize); // インデックスバッファ作成
    HRESULT CreateTexBuff(TexBuff* texBuffObj); // テクスチャバッファオブジェクト作成
    HRESULT CreateConstBuff(ConstBuff* constBuffObj, UINT byteSize); // コンスタントオブジェクト作成
    HRESULT CreateCSUHeap(CSUHeap* csuHeap); // CSUヒープ作成

    void CreateCBV(CBV* cbv, CSUHeap* csuHeap, ConstBuff* constBuff); // CBV作成
    void CreateSRV(SRV* srv, CSUHeap* csuHeap, TexBuff* texBuff); // SRV作成

    ID3D12Device* GetDevice(); // Direct3Dデバイスを渡す

    Device();
    ~Device();
};