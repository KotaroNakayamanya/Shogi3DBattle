#pragma once

#include"HeapFactory.h"
#include"IViewFactory.h"
#include"IBuffFactory.h"

#include"RenderTexBuff.h"
#include"Device11.h"
#include"DeviceContext.h"
#include"CmdAllocator.h"
#include"CmdList.h"
#include"CmdQueue.h"
#include"SwapChain.h"
#include"Heap.h"
#include"View.h"
#include"GameWindow.h"
#include"Buff.h"
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
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Device> _device; // Direct3Dデバイス

    std::unique_ptr<IBuffFactory> _buffFactory; // バッファファクトリー 
    std::unique_ptr<HeapFactory>  _heapFactory; // ヒープファクトリー
    std::unique_ptr<IViewFactory> _viewFactory; // ビューファクトリー

    D3D12_COMMAND_QUEUE_DESC GetCmdQueueDesc(); // コマンドキューディスクリプタ

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


    HRESULT CreateBuff(Buff* buff, UINT width, UINT height, Buff::BuffType buffType); // バッファ作成

    HRESULT CreateDSBuff(Buff* dsBuff, GameWindow* gameWindow); // デプスステンシルバッファ作成
    HRESULT CreateVertBuff(VertBuff* vertBuff, Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces); // 頂点バッファ作成
    HRESULT CreateIdxBuff (IdxBuff* idxBuff,   Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces); // インデックスバッファ作成
    HRESULT CreateConstBuff(ConstBuff* constBuff, UINT pieceNum); // コンスタントバッファ作成
    HRESULT CreateTexBuff(TexBuff* texBuff); // テクスチャバッファ作成
    //HRESULT CreateRenderTexBuff(RenderTexBuff* renderTexBuff, Buff* backBuff); // レンダーターゲット兼テクスチャバッファ作成

    HRESULT CreateHeap   (Heap* heap, UINT descNum, Heap::HeapType heapType); // ヒープ作成
    HRESULT CreateCSUHeap(CSUHeap* csuHeap, UINT cbvNum, UINT srvNum, UINT uavNum, Heap::HeapType heapType); // ヒープ作成（CSU）

    void CreateView   (Heap* heap,       UINT i, Buff* buff, View::ViewType viewType); // ビュー作成
    void CreateCSUView(CSUHeap* csuHeap, UINT i, Buff* buff, View::ViewType viewType); // ビュー作成（CSU系）

    
    
    HRESULT CreateFence(Fence* fence); // フェンス作成

    HRESULT CreateVShader(VShader* vShader); // 頂点シェーダー作成
    HRESULT CreatePShader(PShader* pShader); // ピクセルシェーダー作成

    HRESULT CreateRootSignature(RootSignature* rootSignature); // ルートシグネチャ作成
    void CreateInputLayout(InputLayout* inputLayout); // 入力レイアウト作成
    HRESULT CreatePipeline( // パイプラインステート作成
        Pipeline* pipeline,
        RootSignature* rootSignature,
        InputLayout* inputLayout,
        VShader* vShader,
        PShader* pShader);

    void SetDevice(ComPtr<ID3D12Device> device); // Direct3Dデバイスセット
    ID3D12Device* GetDevice(); // Direct3Dデバイスを返す

    Device();
    ~Device();
};