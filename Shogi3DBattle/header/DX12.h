#pragma once

#include<memory>

#include"DXGIFactory.h"
#include"Adapter.h"
#include"Device.h"
#include"Shader.h"
#include"TBuff.h"
#include"TResource.h"
#include"Draw.h"
#include"VertBuff.h"
#include"IdxBuff.h"
#include"Pawn.h"
#include"ConstBuff.h"
#include"ConstBuffMap.h"
#include"CSUHeap.h"
#include"RootSignature.h"
#include"Pipeline.h"
#include"ViewMat.h"
#include"ProjMat.h"

#include"DrawArg.h"
#include"TextureArg.h"
#include"VertexArg.h"
#include"HeapArg.h"
#include"PipelineArg.h"

class DX12
{
private:
    UINT _windowWidth = 1280;
    UINT _windowHeight = 720;

    const int _buffNum = 2; // 描画に使用する画面数

    std::unique_ptr<DXGIFactory> _dxgiFactory; // DXGIファクトリーオブジェクト
    HRESULT CreateDXGIFactoryObj();            // DXGIファクトリ作成

    std::unique_ptr<Adapter> _adapter; // アダプターオブジェクト

    std::unique_ptr<Device> _device; // Direct3Dデバイスオブジェクト

    std::unique_ptr<Draw> _draw; // 描画オブジェクト
    HRESULT CreateDrawObj(HWND hwnd); // 描画オブジェクト作成
    DrawArg::CreateDrawObjArg // 描画オブジェクト作成用引数
        GetCreateDrawObjArg(HWND hwnd);

    std::unique_ptr<Shader> _shader; // シェーダーオブジェクト
    std::unique_ptr<VertBuff> _vertBuff; // 頂点バッファオブジェクト

    std::unique_ptr<IdxBuff> _idxBuff; // インデックスバッファオブジェクト
    HRESULT CreateIdxBuffObj();       // インデックスバッファオブジェクト作成

    std::unique_ptr<RootSignature> _rootSignature; // ルートシグネチャオブジェクト
    HRESULT CreateRootSignatureObj();              // ルートシグネチャオブジェクト作成

    std::unique_ptr<Pipeline> _pipeline; // パイプラインオブジェクト
    HRESULT CreatePipelineObj();         // パイプラインオブジェクト作成
    PipelineArg::CreatePipelineStateArg  // パイプラインオブジェクト作成用引数
        GetCreatePipelineObjArg(); 

    std::unique_ptr<TBuff> _tBuff; // テクスチャバッファオブジェクト
    HRESULT CreateTBuffObj();    // テクスチャバッファオブジェクト作成
    TextureArg::CreateTextureObjArg    // テクスチャバッファオブジェクト作成用引数
        GetCreateTBuffObjArg();

    std::unique_ptr<ConstBuff> _constBuff; // コンスタントバッファオブジェクト
    HRESULT CreateCBuffObj();              // コンスタントバッファオブジェクト作成

    std::unique_ptr<ConstBuffMap> _constBuffMap; // コンスタントバッファマップオブジェクト
    HRESULT CreateCBuffMapObj();                 // コンスタントバッファマップオブジェクト作成

    std::unique_ptr<CSUHeap> _csuHeap; // CSUヒープオブジェクト
    HRESULT CreateCSUHeapObj();     // CSUヒープオブジェクト作成
    HeapArg::CreateCSUHeapArg // CSUヒープオブジェクト作成用引数
        GetCreateCSUHeapArg();

    std::unique_ptr<ViewMat> _viewMat;

    std::unique_ptr<ProjMat> _projMat;





    DXGI_SAMPLE_DESC GetSampleDesc(); // サンプリングディスクリプタ
 

    
    void PrepareRenderTarget(); // レンダーターゲットの準備

    // コマンドセット
    void SetCommand();

    // 駒オブジェクト
    std::unique_ptr<Pawn> _pawn;
    HRESULT CreateVertexSets();
    
    // コマンドセット
    D3D12_VERTEX_BUFFER_VIEW GetVertexBuffView();
    D3D12_INDEX_BUFFER_VIEW GetIndexBuffView();


    void ExeDraw();
    void ResetCommand();
    void WaitProcessWithFence();


    DrawArg::SetCommandArg // コマンドセット用引数
        GetSetCommandArg();
    
public:
    bool CreateDX12Obj(HWND hwnd); // DirectX12オブジェクト作成
    void ExeDX12(); // DirectX12実行処理

    /// <summary>
    Piece* GetPawn(); // ポーンを返す
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    ViewMat* GetViewMat(); // ビュー行列を返す

    void ProcessChangeWindowSize( // ウインドウサイズ変更処理
        UINT width, UINT height);

    DX12();
    ~DX12();
};