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
#include"InputLayout.h"
#include"Pipeline.h"

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

    D3D12_GRAPHICS_PIPELINE_STATE_DESC GetPipelineStateDesc( // パイプラインステートディスクリプタ
        ID3D12RootSignature* rootSignature,
        std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout,
        ID3DBlob* vShader,
        ID3DBlob* pShader); 
    D3D12_SHADER_BYTECODE GetVertexShaderDesc( // 頂点シェーダーディスクリプタ
        ID3DBlob* vertexShaderBlob);
    D3D12_SHADER_BYTECODE GetPixelShaderDesc(  // ピクセルシェーダーディスクリプタ
        ID3DBlob* pixelShaderBlob);
    D3D12_BLEND_DESC GetBlendStateDesc();                      // ブレンドステートディスクリプタ
    D3D12_RENDER_TARGET_BLEND_DESC GetRenderTargetBlendDesc(); // レンダーターゲットブレンドディスクリプタ
    D3D12_RASTERIZER_DESC GetRasterizerDesc();                 // ラスタライザディスクリプタ
    D3D12_INPUT_LAYOUT_DESC GetInputLayoutDesc(                // インプットレイアウトディスクリプタ
        std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout);
    D3D12_DEPTH_STENCIL_DESC GetDepthStencilDesc(); // デプスステンシルディスクリプタ

public:
    HRESULT CreateVShader(VShader* vShader); // 頂点シェーダーオブジェクト作成
    HRESULT CreatePShader(PShader* pShader); // ピクセルシェーダーオブジェクト作成
    HRESULT CreateVertBuff(VertBuff* vertBuff, UINT byteSize); // 頂点バッファ作成
    HRESULT CreateIdxBuff (IdxBuff* idxBuff,   UINT byteSize); // インデックスバッファ作成
    HRESULT CreateTexBuff(TexBuff* texBuff); // テクスチャバッファオブジェクト作成
    HRESULT CreateConstBuff(ConstBuff* constBuff, UINT byteSize); // コンスタントオブジェクト作成
    HRESULT CreateCSUHeap(CSUHeap* csuHeap); // CSUヒープ作成
    void CreateCBV(CBV* cbv, CSUHeap* csuHeap, ConstBuff* constBuff); // CBV作成
    void CreateSRV(SRV* srv, CSUHeap* csuHeap, TexBuff* texBuff); // SRV作成
    HRESULT CreateRootSignature(RootSignature* rootSignature); // ルートシグネチャ作成
    void CreateInputLayout(InputLayout* inputLayout); // 入力レイアウト作成
    HRESULT CreatePipeline( // パイプラインステート作成
        Pipeline* pipeline,
        RootSignature* rootSignature,
        InputLayout* inputLayout,
        VShader* vShader,
        PShader* pShader);

    ID3D12Device* GetDevice(); // Direct3Dデバイスを渡す

    Device();
    ~Device();
};