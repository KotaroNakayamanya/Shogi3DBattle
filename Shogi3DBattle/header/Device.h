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
#include"RootSignature.h"

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

    ComPtr<ID3DBlob> GetRootSignatureBlob(); // ルートシグネチャBlob取得
    D3D12_ROOT_SIGNATURE_DESC GetRootSignatureDesc(); // ルートシグネチャディスクリプタ
    std::vector<D3D12_ROOT_PARAMETER> GetRootParams(UINT paramNum); // ルートパラメータ
    // ディスクリプタレンジ作成用ステート
    class RangeTypeState
    {
    private:
        UINT rangeNum; // レンジ数
    public:
        // 仮想関数
        virtual std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges() = 0;

        UINT GetRangeNum(){return rangeNum;}

        RangeTypeState(UINT num):rangeNum(num){}
        RangeTypeState()        :rangeNum(-1){}
        ~RangeTypeState(){}
    };

    // CBVディスクリプタレンジ作成
    class RangeTypeCBV : public RangeTypeState
    {
    private:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetCBVDescRanges(); // CBVディスクリプタレンジ
    public:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges() override
        {
            return GetCBVDescRanges();
        }

        RangeTypeCBV(UINT num):RangeTypeState(num){}
        RangeTypeCBV():        RangeTypeState(-1){}
        ~RangeTypeCBV(){}
    };

    // SRVディスクリプタレンジ作成
    class RangeTypeSRV : public RangeTypeState
    {
    private:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetSRVDescRanges(); // SRVディスクリプタレンジ
    public:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges() override
        {
            return GetSRVDescRanges();
        }

        RangeTypeSRV(UINT num):RangeTypeState(num){}
        RangeTypeSRV():        RangeTypeState(-1){}
        ~RangeTypeSRV(){}
    };
    D3D12_ROOT_DESCRIPTOR_TABLE GetDescTable(RangeTypeState* rangeType); // ディスクリプタテーブル
    std::vector<D3D12_STATIC_SAMPLER_DESC> GetSamplerDescs(UINT samplerNum); // サンプラーディスクリプタ
    void DeleteRootSignatureDescMemory(D3D12_ROOT_SIGNATURE_DESC* desc); // ディスクリプタで使用されたメモリ開放

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
    HRESULT CreateRootSignature(RootSignature* rootSignature); // ルートシグネチャ作成  

    ID3D12Device* GetDevice(); // Direct3Dデバイスを渡す

    Device();
    ~Device();
};