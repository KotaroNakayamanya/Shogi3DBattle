#pragma once

#include<memory>
#include"DXGIFactory.h"
#include"Device.h"
#include"DWriteFactory.h"

#include"Viewport.h"
#include"ScissorRect.h"

#include"ViewMat.h"
#include"ProjMat.h"

#include"Pawn.h"
#include"Board.h"

#include"Tex.h"

class DX12
{
private:
    const int _rtBuffNum = 2; // 描画に使用する画面数

    std::unique_ptr<DXGIFactory> _dxgiFactory; // DXGIファクトリー
    std::unique_ptr<Adapter>     _adapter;     // アダプター
    std::unique_ptr<Device>      _device;      // Direct3D12デバイス

    std::unique_ptr<DWriteFactory> _dWriteFactory; // DirectWriteFactory
    std::unique_ptr<Device11>      _device11;      // Direct3D11デバイス
    std::unique_ptr<DeviceContext> _deviceContext; // デバイスコンテキスト
    std::unique_ptr<D2DDeviceContext> _d2dDeviceContext; // Direct2Dデバイスコンテキスト
    std::unique_ptr<D2DSolidColorBrush> _d2dSolidColorBrush; // Direct2Dソリッドカラーブラッシュ

    std::unique_ptr<DWriteTextFormat> _dWriteTextFormat; // ディレクトライトテキストフォーマット

    std::unique_ptr<DWriteTextFormat> _pieceTextFormat; // 駒のテキストフォーマット

    std::vector<std::unique_ptr<WrappedBackBuffer>> _wrappedBackBuffers; // ラップされたバックバッファ
    std::vector<std::unique_ptr<D2DRenderTarget>> _d2dRenderTargets; // Direct2Dレンダーターゲット

    std::unique_ptr<CmdAllocator> _cmdAllocator; // コマンドアロケータ
    std::unique_ptr<CmdList> _cmdList; // コマンドリスト
    std::unique_ptr<CmdQueue> _cmdQueue; // コマンドリスト
    std::unique_ptr<SwapChain> _swapChain; // スワップチェーン
    std::unique_ptr<RTVHeap> _rtvHeap; // RTVヒープ
    std::vector<std::unique_ptr<BackBuff>> _backBuffs; // バックバッファ
    std::unique_ptr<DSBuff> _dsBuff; // デプスステンシルバッファ
    std::unique_ptr<DSVHeap> _dsvHeap; // デプスステンシルヒープ
    std::unique_ptr<DSV> _dsv; // デプスステンシルビュー
    std::unique_ptr<Fence> _fence; // フェンス

    std::unique_ptr<Viewport> _viewport; // ビューポート
    std::unique_ptr<ScissorRect> _scissorRect; // シザー矩形

    std::unique_ptr<VShader> _vShader; // 頂点シェーダー
    std::unique_ptr<PShader> _pShader; // ピクセルシェーダー

    std::unique_ptr<VertBuff> _vertBuff; // 頂点バッファ
    std::unique_ptr<IdxBuff>  _idxBuff;  // インデックスバッファ

    std::unique_ptr<InputLayout> _inputLayout; // 入力レイアウト
    std::unique_ptr<RootSignature> _rootSignature; // ルートシグネチャ
    std::unique_ptr<Pipeline> _pipeline; // パイプライン

    std::unique_ptr<ConstBuff> _constBuff; // コンスタントバッファ

    std::unique_ptr<TexBuff>   _texBuff; // テクスチャバッファ
    std::unique_ptr<Tex>       _tex;     // テクスチャ

    std::vector<std::unique_ptr<RenderTexBuff>> _pieceTexBuffs; // 駒テクスチャバッファ

    std::unique_ptr<CSUHeap>   _csuHeap; // CSUヒープ

    std::unique_ptr<ViewMat> _viewMat; // ビュー行列
    std::unique_ptr<ProjMat> _projMat; // プロジェクション行列

    std::unique_ptr<Board> _board; // 将棋盤

    std::array<std::unique_ptr<Piece>, 40> _pieces; // 駒



    HRESULT CreateDXGIFactory(); // DXGIファクトリー作成
    HRESULT CreateDWriteFactory(); // DirectWriteファクトリー作成

    void CreateTex(); // テクスチャ作成

    void CreateBoard(ShogiObjId id); // 将棋盤作成
    void CreatePiece(Piece* piece, ShogiObjId id); // 駒作成

    void StartD2D(); // Direct2D開始
    void EndD2D();   // Direct2D終了
    void DrawStr(std::wstring str, D2D1_RECT_F rect); // 文字を出力する





    void PrepareRenderTarget(); // レンダーターゲットの準備
    void ChangeBarrierToRenderTarget(BackBuff* backBuff); // レンダーターゲットに変更
    void ChangeBarrierToPresent     (BackBuff* backBuff); // 画面表示用に変更
    D3D12_RESOURCE_BARRIER GetBasiceResourceBarrier(); // リソースバリア基本設定

    void SetCommand(); // コマンドセット
    D3D12_VERTEX_BUFFER_VIEW GetVertBuffView(ShogiObj* obj); // 頂点バッファビュー
    D3D12_INDEX_BUFFER_VIEW  GetIdxBuffView (ShogiObj* obj); // インデックスバッファビュー

    void ExeCommand(); // コマンド実行

    void SetCmdDrawObj(ShogiObj* shogiObj);
    
   


    void ExeDraw();
    void ResetCommand();
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