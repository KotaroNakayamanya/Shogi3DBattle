#pragma once

#include<memory>

#include"DXGIFactory.h"
#include"Device.h"
#include"DWriteFactory.h"

#include"Viewport.h"
#include"ScissorRect.h"
#include"ResourceBarrier.h"
#include"ViewMat.h"
#include"ProjMat.h"

#include"Board.h"

class DX12
{
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
    std::unique_ptr<VertBuff> _vertBuff; // 頂点バッファ
    std::unique_ptr<IdxBuff>  _idxBuff;  // インデックスバッファ
    std::unique_ptr<ConstBuff> _constBuff; // コンスタントバッファ
    std::unique_ptr<TexBuff>   _texBuff; // テクスチャバッファ
    std::vector<std::unique_ptr<RenderTexBuff>> _pieceTexBuffs; // 駒テクスチャバッファ
    HRESULT CreateBuff(); // バッファ系作成
    HRESULT WriteToBuff(); // バッファに書き込み  

    // ヒープ
    std::unique_ptr<Heap>    _rtvHeap; // RTVヒープ
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

    
    // Direct2Dテキストフォーマット
    std::unique_ptr<DWriteTextFormat>   _dWriteTextFormat;   // ディレクトライトテキストフォーマット
    std::unique_ptr<DWriteTextFormat> _pieceTextFormat; // 駒のテキストフォーマット

    // Direct2Dソリッドカラーブッシュ
    std::unique_ptr<D2DSolidColorBrush> _d2dSolidColorBrush; // Direct2Dソリッドカラーブラッシュ

    // Direct2Dバックバッファ
    std::vector<std::unique_ptr<WrappedBackBuff>> _wrappedBackBuffs; // ラップされたバックバッファ

    // Direct2Dレンダーターゲット
    std::vector<std::unique_ptr<D2DRenderTarget>> _d2dRenderTargets; // Direct2Dレンダーターゲット
    
    
    // その他
    std::unique_ptr<Fence> _fence; // フェンス
    std::unique_ptr<ResourceBarrier> _rb; // リソースバリア

    // 描画領域
    std::unique_ptr<Viewport> _viewport; // ビューポート
    std::unique_ptr<ScissorRect> _scissorRect; // シザー矩形
    void CreateDrawArea(); // 描画領域系作成

    // シェーダー
    std::unique_ptr<VShader> _vShader; // 頂点シェーダー
    std::unique_ptr<PShader> _pShader; // ピクセルシェーダー
    HRESULT CreateShader(); // シェーダー系作成

    std::unique_ptr<InputLayout> _inputLayout; // 入力レイアウト
    std::unique_ptr<RootSignature> _rootSignature; // ルートシグネチャ
    std::unique_ptr<Pipeline> _pipeline; // パイプライン

    // テクスチャ
    std::unique_ptr<Tex> _tex;     // テクスチャ
    void CreateTex(); // テクスチャ作成


    
    

    
    // カメラ
    std::unique_ptr<ViewMat> _viewMat; // ビュー行列
    std::unique_ptr<ProjMat> _projMat; // プロジェクション行列

    // 将棋オブジェクト
    std::unique_ptr<Board> _board; // 将棋盤
    std::array<std::unique_ptr<Piece>, 40> _pieces; // 駒


    void CreateBoard(ShogiObjId id); // 将棋盤作成
    void CreatePiece(Piece* piece, ShogiObjId id); // 駒作成

    void InitRenderTarget(); // レンダーターゲット初期処理

    void ExeD3D(); // Direct3D処理実行
    void ExeD2D(); // Direct2D処理実行

    void PrepareRenderTargetToFlip(); // レンダーターゲットのフリップ準備

    void StartD2D(); // Direct2D開始
    void EndD2D();   // Direct2D終了
    void DrawStr(    // 文字を出力する
        std::wstring str,
        float left,
        float top,
        float right,
        float bottom);


    void Set3DCmd(); // 3Dコマンドセット
    D3D12_VERTEX_BUFFER_VIEW GetVertBuffView(ShogiObj* obj); // 頂点バッファビュー
    D3D12_INDEX_BUFFER_VIEW  GetIdxBuffView (ShogiObj* obj); // インデックスバッファビュー


    void ExeCmd(); // コマンド実行

    void SetDrawObjCmd(ShogiObj* shogiObj); // オブジェクト描画コマンドセット
    
  
    void WaitProcessWithFence();
    
public:
    bool InitDX12(GameWindow* gameWindow); // DirectX12初期作成
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