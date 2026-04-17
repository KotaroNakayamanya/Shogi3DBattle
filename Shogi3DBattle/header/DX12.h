#pragma once

#include<memory>

#include"DXGIFactory.h"
#include"Device.h"
#include"DirectWriteFactory.h"

#include"ResourceBarrier.h"
#include"ViewMat.h"

#include"GameObjType.h"
#include"NaturalBufferedData.h"

#include"Vert.h"

#include<wrl.h>

#include"Direct2DFactory.h"
#include"Direct2DDevice.h"
#include"Device11AndDeviceContext.h"

class DX12
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    unsigned int _currentBackBuffIdx; // 現在のバックバッファインデックス

    // DXGIファクトリー
    std::unique_ptr<DXGIFactory> _dxgiFactory; // DXGIファクトリー

    std::unique_ptr<Device>      _device;      // Direct3Dデバイス

    // コマンド
    ComPtr<ID3D12CommandAllocator>    _cmdAllocator; // コマンドアロケータ
    ComPtr<ID3D12GraphicsCommandList> _cmdList;      // コマンドリスト
    ComPtr<ID3D12CommandQueue>        _cmdQueue;     // コマンドリスト

    // スワップチェーン
    ComPtr<IDXGISwapChain4> _swapChain; // スワップチェーン

    // バッファ
    std::vector<ComPtr<ID3D12Resource>> _backBuffs; // バックバッファ
    ComPtr<ID3D12Resource>              _dsBuff;    // デプスステンシルバッファ
    ComPtr<ID3D12Resource>              _vertBuff;  // 頂点バッファ
    ComPtr<ID3D12Resource>              _idxBuff;   // インデックスバッファ
    ComPtr<ID3D12Resource>              _constBuff; // コンスタントバッファ

    std::vector<ComPtr<ID3D12Resource>> _woodTexBuffs; // 木材テクスチャバッファ
    std::vector<ComPtr<ID3D12Resource>> _shogiObjTexBuffs; // 将棋オブジェクト種類ごとのテクスチャバッファ

    std::vector<ComPtr<ID3D11Resource>> _wrappedPieceTexBuffs; // ラップされた駒テクスチャバッファ
    std::vector<ComPtr<ID2D1Bitmap1>> _d2dPieceTexRenderTargets; // 駒テクスチャ作成用レンダーターゲット

    void CreateRenderTex(); // レンダーテクスチャ作成
    void CreatePieceTex(
        GameObjType shogiObjType,
        std::wstring frontText,
        std::wstring backText); // 駒テクスチャ作成

    void InitRenderTex(GameObjType shogiObjType); // レンダーテクスチャ初期処理
    void ExitRenderTex(GameObjType shogiObjType); // レンダリング終了処理

    void CreateBuff(); // バッファ系作成
    void WriteToBuff(); // バッファに書き込み  

    // ヒープ
    std::unique_ptr<Heap>    _rtvHeap; // RTVヒープ
    std::unique_ptr<Heap>    _texRTVHeap; // テクスチャRTVヒープ
    std::unique_ptr<Heap>    _dsvHeap; // DSVヒープ
    std::unique_ptr<CSUHeap> _csuHeap; // CSUヒープ
    std::unique_ptr<Heap>    _pieceTexRTVHeap; // 駒テクスチャRTVヒープ
    std::unique_ptr<CSUHeap> _pieceTexSRVHeap; // 駒テクスチャSRVヒープ
    void CreateHeap(); // ヒープ作成

    // ビュー
    void CreateView(); // ビュー作成

    // DirectX11デバイス
    std::unique_ptr<Device11>   _device11;         // Direct3D(11)デバイス
    ComPtr<ID3D11DeviceContext> _deviceContext;    // デバイスコンテキスト
    Device11AndDeviceContext CreateDX11Device(); // DirectX11系デバイス作成

    // Direct2Dファクトリー
    std::unique_ptr<Direct2DFactory> _direct2DFactory;        // Direct2Dファクトリー
    std::unique_ptr<Direct2DFactory> CreateDirect2DFactory(); // Direct2Dファクトリー作成

    // Direct2Dデバイス
    std::unique_ptr<Direct2DDevice>        _direct2DDevice;
    std::unique_ptr<Direct2DDeviceContext> _direct2DDeviceContext; // Direct2Dデバイスコンテキスト
    void CreateD2D(); // Direct2D系作成

    
    // テキストフォーマット
    std::unique_ptr<DirectWriteFactory> _directWriteFactory;    // DirectWriteファクトリー
    ComPtr<IDWriteTextFormat> _pieceTextFormat; // 駒のテキストフォーマット
    ComPtr<IDWriteTextFormat> _normalTextFormat; // 通常テキストフォーマット
    ComPtr<IDWriteTextFormat> _boldTextFormat;   // 太めテキストフォーマット

    // ブラシ
    ComPtr<ID2D1SolidColorBrush> _blackBrush; // 黒色ブラシ
    ComPtr<ID2D1SolidColorBrush> _redBrush;   // 赤色ブラシ
    ComPtr<ID2D1SolidColorBrush> _yellowBrush;   // 黄色ブラシ
    ComPtr<ID2D1SolidColorBrush> _buttonUIBackBrush;    // ボタンUI背景ブラシ
    

        

    // Direct2Dラップバッファ
    std::vector<ComPtr<ID3D11Resource>> _wrappedBackBuffs; // ラップされたバックバッファ

    // Direct2Dレンダーターゲット
    std::vector<ComPtr<ID2D1Bitmap1>> _d2dRenderTargets; // Direct2Dレンダーターゲット
    
    
    // その他
    unsigned int        _fenceVal; // フェンス値記録
    ComPtr<ID3D12Fence> _fence; // フェンス
    std::unique_ptr<ResourceBarrier> _rb; // リソースバリア

    // 描画領域
    std::unique_ptr<D3D12_VIEWPORT> _mainViewport;    // メインビューポート
    std::unique_ptr<D3D12_RECT>     _mainScissorRect; // メインシザー矩形
    std::unique_ptr<D3D12_VIEWPORT> _mapViewport;     // マップビューポート
    std::unique_ptr<D3D12_RECT>     _mapScissorRect;  // マップシザー矩形

    void CreateDrawArea(); // 描画領域系作成

    // シェーダー
    ComPtr<ID3DBlob> _vShader;     // 頂点シェーダー
    ComPtr<ID3DBlob> _pShader;     // ピクセルシェーダー
    ComPtr<ID3DBlob> CreateShader( // シェーダー作成
        std::wstring fileName,
        std::string funcName,
        std::string shaderType);
    

    ComPtr<ID3D12RootSignature> _rootSignature; // ルートシグネチャ
    ComPtr<ID3D12PipelineState> _pipeline; // パイプライン

    void InitRenderTarget(); // レンダーターゲット初期処理

    void ExeD3D(); // Direct3D処理実行
    void ExeD2D(); // Direct2D処理実行

    void PrepareRenderTargetToFlip(); // レンダーターゲットのフリップ準備

    void StartD2D(ID3D11Resource** wrappedBuffAddress, ID2D1Bitmap1* d2dRenderTarget); // Direct2D開始
    void EndD2D(ID3D11Resource** wrappedBuffAddresss);   // Direct2D終了
    


    void Set3DCmd(); // 3Dコマンドセット
    D3D12_VERTEX_BUFFER_VIEW GetVertBuffView(NaturalBufferedData<Vert>* vertices); // 頂点バッファビュー
    D3D12_INDEX_BUFFER_VIEW  GetIdxBuffView (NaturalBufferedData<unsigned short>* vertIndices); // インデックスバッファビュー


    void ExeCmd(); // コマンド実行
    
  
    void WaitProcessWithFence();

    void SetCommandDrawGameObj(); // ゲームオブジェクト描画コマンドセット
    
public:
    void InitDX12(); // DirectX12初期作成
    void ExeDX12(); // DirectX12実行処理

    IDWriteTextFormat*    GetNormalTextFormat(); // 通常のテキストフォーマットを返す
    IDWriteTextFormat*    GetBoldTextFormat();   // 太めのテキストフォーマットを返す
    ID2D1SolidColorBrush* GetBlackBrush();       // 黒色ブラシを返す
    ID2D1SolidColorBrush* GetYellowBrush();      // 黄色ブラシを返す

    void ProcessChangeWindowSize( // ウインドウサイズ変更処理
        UINT width, UINT height);

    DX12();
};