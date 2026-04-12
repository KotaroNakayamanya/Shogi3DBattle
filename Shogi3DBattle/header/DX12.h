#pragma once

#include<memory>

#include"DXGIFactory.h"
#include"Device.h"
#include"DWriteFactory.h"

#include"ResourceBarrier.h"
#include"ViewMat.h"

#include"GameObjType.h"
#include"NaturalBufferedData.h"

#include"Vert.h"

#include<wrl.h>

class DX12
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    UINT _currentBackBuffIdx; // 現在のバックバッファインデックス

    // ファクトリー系
    std::unique_ptr<DXGIFactory> _dxgiFactory; // DXGIファクトリー
    std::unique_ptr<Adapter>     _adapter;     // アダプター
    std::unique_ptr<Device>      _device;      // Direct3D12デバイス
    HRESULT CreateFactory(); // ファクトリー系作成
    HRESULT CreateDXGIFactory(); // DXGIファクトリー作成

    // コマンド
    std::unique_ptr<CmdAllocator> _cmdAllocator; // コマンドアロケータ
    std::unique_ptr<CmdList> _cmdList; // コマンドリスト
    std::unique_ptr<CmdQueue> _cmdQueue; // コマンドリスト
    HRESULT CreateCommand(); // コマンド系作成

    // スワップチェーン
    std::unique_ptr<SwapChain> _swapChain; // スワップチェーン

    // バッファ
    std::vector<std::unique_ptr<Buff>> _backBuffs; // バックバッファ
    std::unique_ptr<Buff> _dsBuff; // デプスステンシルバッファ
    std::unique_ptr<Buff> _vertBuff; // 頂点バッファ
    std::unique_ptr<Buff> _idxBuff;  // インデックスバッファ
    std::unique_ptr<Buff> _constBuff; // コンスタントバッファ

    std::unique_ptr<Buff>   _woodTexBuff; // 木材テクスチャバッファ
    std::vector<std::unique_ptr<Buff>> _shogiObjTexBuffs; // 将棋オブジェクト種類ごとのテクスチャバッファ

    std::vector<std::unique_ptr<WrappedBuff>> _wrappedPieceTexBuffs; // ラップされた駒テクスチャバッファ
    std::vector<std::unique_ptr<D2DRenderTarget>> _d2dPieceTexRenderTargets; // 駒テクスチャ作成用レンダーターゲット

    void CreateRenderTex(); // レンダーテクスチャ作成
    void CreatePieceTex(
        GameObjType shogiObjType,
        std::wstring frontText,
        std::wstring backText); // 駒テクスチャ作成

    void InitRenderTex(GameObjType shogiObjType); // レンダーテクスチャ初期処理
    void ExitRenderTex(GameObjType shogiObjType); // レンダリング終了処理

    HRESULT CreateBuff(); // バッファ系作成
    HRESULT WriteToBuff(); // バッファに書き込み  

    // ヒープ
    std::unique_ptr<Heap>    _rtvHeap; // RTVヒープ
    std::unique_ptr<Heap>    _texRTVHeap; // テクスチャRTVヒープ
    std::unique_ptr<Heap>    _dsvHeap; // DSVヒープ
    std::unique_ptr<CSUHeap> _csuHeap; // CSUヒープ
    std::unique_ptr<Heap>    _pieceTexRTVHeap; // 駒テクスチャRTVヒープ
    std::unique_ptr<CSUHeap> _pieceTexSRVHeap; // 駒テクスチャSRVヒープ
    HRESULT CreateHeap(); // ヒープ作成

    // ビュー
    void CreateView(); // ビュー作成

    // Direct2D
    std::unique_ptr<Device11>         _device11;         // Direct3D11デバイス
    std::unique_ptr<DeviceContext>    _deviceContext;    // デバイスコンテキスト
    std::unique_ptr<D2DDeviceContext> _d2dDeviceContext; // Direct2Dデバイスコンテキスト
    std::unique_ptr<DWriteFactory>    _dWriteFactory;    // DirectWriteファクトリー
    HRESULT CreateD2D(); // Direct2D系作成
    HRESULT CreateDWriteFactory(); // DirectWriteファクトリー作成

    
    // テキストフォーマット
    std::unique_ptr<TextFormat> _pieceTextFormat; // 駒のテキストフォーマット
    std::unique_ptr<TextFormat> _normalTextFormat; // UIテキストフォーマット

    // ブラシ
    //std::unique_ptr<Brush> _blackBrush; // 黒色ブラシ
    //std::unique_ptr<Brush> _redBrush;   // 赤色ブラシ
    //std::unique_ptr<Brush> _buttonUIBackBrush;    // ボタンUI背景ブラシ
    ComPtr<ID2D1SolidColorBrush> _blackBrush; // 黒色ブラシ
    ComPtr<ID2D1SolidColorBrush> _redBrush;   // 赤色ブラシ
    ComPtr<ID2D1SolidColorBrush> _buttonUIBackBrush;    // ボタンUI背景ブラシ
    

        

    // Direct2Dラップバッファ
    std::vector<std::unique_ptr<WrappedBuff>> _wrappedBackBuffs; // ラップされたバックバッファ

    // Direct2Dレンダーターゲット
    std::vector<std::unique_ptr<D2DRenderTarget>> _d2dRenderTargets; // Direct2Dレンダーターゲット
    
    
    // その他
    std::unique_ptr<Fence> _fence; // フェンス
    std::unique_ptr<ResourceBarrier> _rb; // リソースバリア

    // 描画領域
    std::unique_ptr<D3D12_VIEWPORT> _mainViewport;    // メインビューポート
    std::unique_ptr<D3D12_RECT>     _mainScissorRect; // メインシザー矩形
    std::unique_ptr<D3D12_VIEWPORT> _mapViewport;     // マップビューポート
    std::unique_ptr<D3D12_RECT>     _mapScissorRect;  // マップシザー矩形

    void CreateDrawArea(); // 描画領域系作成

    // シェーダー
    std::unique_ptr<Shader> _vShader; // 頂点シェーダー
    std::unique_ptr<Shader> _pShader; // ピクセルシェーダー
    HRESULT CreateShader(); // シェーダー系作成

    std::unique_ptr<InputLayout> _inputLayout; // 入力レイアウト
    std::unique_ptr<RootSignature> _rootSignature; // ルートシグネチャ
    std::unique_ptr<Pipeline> _pipeline; // パイプライン

    void InitRenderTarget(); // レンダーターゲット初期処理

    void ExeD3D(); // Direct3D処理実行
    void ExeD2D(); // Direct2D処理実行

    void PrepareRenderTargetToFlip(); // レンダーターゲットのフリップ準備

    void StartD2D(WrappedBuff* wrappedBuff, D2DRenderTarget* d2dRenderTarget); // Direct2D開始
    void EndD2D(WrappedBuff* wrappedBuff);   // Direct2D終了
    


    void Set3DCmd(); // 3Dコマンドセット
    D3D12_VERTEX_BUFFER_VIEW GetVertBuffView(NaturalBufferedData<Vert>* vertices); // 頂点バッファビュー
    D3D12_INDEX_BUFFER_VIEW  GetIdxBuffView (NaturalBufferedData<unsigned short>* vertIndices); // インデックスバッファビュー


    void ExeCmd(); // コマンド実行
    
  
    void WaitProcessWithFence();
    
public:
    bool InitDX12(GameWindow* gameWindow); // DirectX12初期作成
    void ExeDX12(); // DirectX12実行処理

    IDWriteTextFormat*    GetNormalTextFormat(); // 通常のテキストフォーマットを返す
    ID2D1SolidColorBrush* GetBrackBrush();       // 黒色ブラシを返す

    void ProcessChangeWindowSize( // ウインドウサイズ変更処理
        UINT width, UINT height);

    DX12();
    ~DX12() = default;
};