#pragma once

#include"RenderTexBuff.h"
#include"Device11.h"
#include"DeviceContext.h"
#include"CmdAllocator.h"
#include"CmdList.h"
#include"CmdQueue.h"
#include"SwapChain.h"
#include"RTVHeap.h"
#include"GameWindow.h"
#include"BackBuff.h"
#include"DSBuff.h"
#include"DSVHeap.h"
#include"DSV.h"
#include"Fence.h"
#include"VShader.h"
#include"PShader.h"
#include"VertBuff.h"
#include"IdxBuff.h"
#include"TexBuff.h"
#include"ConstBuff.h"
#include"CSUHeap.h"
#include"RootSignature.h"
#include"InputLayout.h"
#include"Pipeline.h"

#include"Board.h"
#include"Piece.h"

class Device
{
    friend class DXGIFactory; // DXGIFactoryから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Device> _device; // Direct3Dデバイス

    D3D12_COMMAND_QUEUE_DESC GetCmdQueueDesc(); // コマンドキューディスクリプタ
    D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc(UINT rtBuffNum); // RTVヒープディスクリプタ

    D3D12_HEAP_PROPERTIES GetVertHeapProp(); // 頂点ヒーププロパティ
    D3D12_RESOURCE_DESC GetVertResourceDesc(UINT byteSize);  // 頂点リソースディスクリプタ

    D3D12_HEAP_PROPERTIES GetTexHeapProp();   // テクスチャヒーププロパティ
    D3D12_RESOURCE_DESC GetTexResourceDesc(); // テクスチャリソースディスクリプタ
    DXGI_SAMPLE_DESC GetSampleDesc(); // サンプリングディスクリプタ

    D3D12_HEAP_PROPERTIES GetConstHeapProp(); // コンスタントヒーププロパティ
    D3D12_RESOURCE_DESC GetConstResourceDesc(UINT pieceNum); // コンスタントリソースディスクリプタ

    D3D12_HEAP_PROPERTIES GetDefaultHeapProp(); // デフォルトヒーププロパティ
    D3D12_RESOURCE_DESC GetDSResourceDesc( // デプスステンシルリソースディスクリプタ
        UINT windowWidth, UINT windowHeight);   
    D3D12_CLEAR_VALUE GetClearValue(); // クリアバリュー

    D3D12_DESCRIPTOR_HEAP_DESC GetDSVHeapDesc(); // DSVヒープディスクリプタ
    D3D12_DEPTH_STENCIL_VIEW_DESC GetDSVDesc(); // DSVディスクリプタ

    D3D12_DESCRIPTOR_HEAP_DESC GetCSUHeapDesc(UINT descNum); // CSUヒープディスクリプタ
    D3D12_CONSTANT_BUFFER_VIEW_DESC GetCBVDesc(ID3D12Resource* constBuff); // CBVディスクリプタ
    D3D12_SHADER_RESOURCE_VIEW_DESC GetSRVDesc(); // SRVディスクリプタ

    ComPtr<ID3DBlob> GetRootSignatureBlob(); // ルートシグネチャBlob取得
    D3D12_ROOT_SIGNATURE_DESC GetRootSignatureDesc(); // ルートシグネチャディスクリプタ
    std::vector<D3D12_ROOT_PARAMETER> GetRootParams(UINT paramNum); // ルートパラメータ
    D3D12_ROOT_DESCRIPTOR_TABLE GetDescTable( // ディスクリプタテーブル
        D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
        UINT rangeNum);
    std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges( // ディスクリプタレンジ
        D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
        UINT rangeNum);

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
    HRESULT CreateCmdAllocator(CmdAllocator* comAllocator); // コマンドアロケータ作成
    HRESULT CreateCmdList(CmdList* comList, CmdAllocator* comAllocator); // コマンドリスト作成
    HRESULT CreateCmdQueue(CmdQueue* comQueue); // コマンドキュー作成
    HRESULT CreateD3D11( // Direct3D11系作成
        Device11* device11,
        DeviceContext* deviceContext,
        CmdQueue* cmdQueue);
    HRESULT CreateRTVHeap(RTVHeap* rtvHeap, SwapChain* swapChain); // RTVヒープ作成
    HRESULT CreateRTV(BackBuff* backBuff, RTVHeap* rtvHeap, SwapChain* swapChain, UINT i); // RTV作成
    HRESULT CreateDSBuff(DSBuff* dsBuff, GameWindow* gameWindow); // デプスステンシルバッファ作成
    HRESULT CreateDSVHeap(DSVHeap* dsvHeap); // デプスステンシルヒープ作成
    void    CreateDSV(DSV* dsv, DSVHeap* dsvHeap, DSBuff* dsBuff); // DSV作成
    HRESULT CreateFence(Fence* fence); // フェンス作成

    HRESULT CreateVShader(VShader* vShader); // 頂点シェーダー作成
    HRESULT CreatePShader(PShader* pShader); // ピクセルシェーダー作成

    HRESULT CreateVertBuff(VertBuff* vertBuff, Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces); // 頂点バッファ作成
    HRESULT CreateIdxBuff (IdxBuff* idxBuff,   Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces); // インデックスバッファ作成


    HRESULT CreateConstBuff(ConstBuff* constBuff, UINT pieceNum); // コンスタントバッファ作成
    HRESULT CreateTexBuff(TexBuff* texBuff); // テクスチャバッファ作成
    HRESULT CreateRenderTexBuff(RenderTexBuff* renderTexBuff); // レンダーターゲット兼テクスチャバッファ作成

    HRESULT CreateCSUHeap(CSUHeap* csuHeap); // CSUヒープ作成
    void    CreateCBV(CSUHeap* csuHeap, ConstBuff* constBuff); // CBV作成
    void    CreateSRV(CSUHeap* csuHeap, TexBuff* texBuff); // SRV作成

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