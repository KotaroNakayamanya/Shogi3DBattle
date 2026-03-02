#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<memory>
#include<wrl.h>
#include<vector>
#include<array>

#include"DrawArgument.h"

class Draw;
class Object;

class DX12
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    HWND _hwnd; // ウインドウハンドル

    const int _bufferNum = 2; // 描画に使用する画面数


    ComPtr<ID3D12Device>  _device;      // Direct3Dデバイス
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリ

    HRESULT CreateDevice();  // Direct3Dデバイス作成
    HRESULT CreateFactory(); // DXGIファクトリ作成

    ComPtr<IDXGIAdapter> GetUsingAdapter(); // 使用するアダプターを取得
    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプターを取得
 

    
 
    HRESULT CreateVertexBuffer(); // 頂点バッファ作成
    HRESULT CreateIndexBuffer(); // インデックスバッファ作成

    HRESULT LoadShaderFile();       // シェーダファイルのロード
    HRESULT LoadVertexShaderFile(); // 頂点シェーダロード
    HRESULT LoadPixelShaderFile();  // ピクセルシェーダロード

    ComPtr<ID3DBlob> _vertexShaderBinary; // 頂点シェーダーバイナリ
    ComPtr<ID3DBlob> _pixelShaderBinary; // ピクセルシェーダバイナリ
    ComPtr<ID3DBlob> _rootSignatureBinary; // ルートシグネチャバイナリ
    ComPtr<ID3DBlob> _errorBinary; // エラーバイナリ


    ComPtr<ID3D12PipelineState> _pipelineState; //パイプラインステート

    HRESULT CreatePipelineState(); // パイプラインステート作成
    D3D12_GRAPHICS_PIPELINE_STATE_DESC GetPipelineStateDesc(); // パイプラインステートディスクリプタ

    ComPtr<ID3D12RootSignature> _rootSignature; // ルートシグネチャ
    std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout;




    D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc();

    
    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc(); // コマンドキューディスクリプタ
    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc(); // スワップチェーンディスクリプタ

    D3D12_HEAP_PROPERTIES GetHeapProperty();
    D3D12_RESOURCE_DESC GetResourceDesc();

    D3D12_SHADER_BYTECODE GetVertexShaderDesc();
    D3D12_SHADER_BYTECODE GetPixelShaderDesc();
    D3D12_RASTERIZER_DESC GetRasterizerDesc();
    D3D12_BLEND_DESC GetBlendStateDesc();
    D3D12_RENDER_TARGET_BLEND_DESC GetRenderTargetBlendDesc();
    D3D12_INPUT_LAYOUT_DESC GetInputLayoutDesc();
    DXGI_SAMPLE_DESC GetSampleDesc();
    D3D12_ROOT_SIGNATURE_DESC GetRootSignatureDesc();

    HRESULT CreateRootSignatureBinary();
    HRESULT CreateRootSignature();

    

    HRESULT MapVertexToBuffer();
    HRESULT MapIndexToBuffer();


    

    void CreateInputLayout();

    // ビューポート
    D3D12_VIEWPORT GetViewports();
    // シザー矩形
    D3D12_RECT GetScissorRects();

    // レンダーターゲットの準備
    void PrepareRenderTarget();

    // コマンドセット
    void SetCommand();

    
    



    // バッファオブジェクト
    ComPtr<ID3D12Resource> _vertexBuffer;
    ComPtr<ID3D12Resource> _indexBuffer;

    // 頂点オブジェクト
    std::vector<std::shared_ptr<Object>> _objects;
    HRESULT CreateVertexSets();
    
    // 描画オブジェクト
    std::shared_ptr<Draw> _draw; 

    HRESULT CreateDrawObject();

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);
    
    D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
    D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();

    //void ExecuteDraw();

    void ExecuteDraw();

    void ExecuteCommand();
    void ResetCommand();

    void WaitProcessWithFence();

    // リソースバリア
    D3D12_RESOURCE_BARRIER GetResourceBarrier();

    
    // 描画オブジェクト作成用引数
    DrawArgument::CreateDrawObjectArgument GetCreateDrawObjectArgument();
    // レンダーターゲット準備用引数
    DrawArgument::PrepareRenderTargetArgument GetPrepareRenderTargetArgument();
    // コマンドセット用引数
    DrawArgument::SetCommandArgument GetSetCommandArgument();
    // コマンド実行用引数
    DrawArgument::ExecuteDrawArgument GetExecuteDrawArgument();
    




public:
    DX12(HWND hwnd);
    ~DX12();

    bool CreateDX12Object();
    void ExecuteDX12();
};