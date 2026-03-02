#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<memory>
#include<wrl.h>
#include<vector>
#include<array>

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


    ComPtr<ID3D12DescriptorHeap>        _rtvHeap; // RTVヒープ
    std::vector<ComPtr<ID3D12Resource>> _rtvs;    // RTV

    HRESULT CreateRTVHeap(); // RTVヒープ作成
    HRESULT CreateRTV();     // RTV作成


    // GPU機能レベル一覧
    std::array<D3D_FEATURE_LEVEL, 5> _featureLevels =
    {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };

    std::vector<ComPtr<IDXGIAdapter>> _adapters;     // 搭載されているアダプターリスト
    ComPtr<IDXGIAdapter>              _usingAdapter; // 使用するアダプター

    void CreateUsedAdapterLists(); // 搭載されているアダプターリストの作成
    void DecisionUsingAdapter();   // 使用するアダプターの決定
 

    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc(); // スワップチェーンディスクリプタ
 
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




    HRESULT SetBufferToRTV(UINT);
    D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc();

    
    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc();


    D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle(UINT idx);

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


    // パイプラインセット
    void SetPipeLineState();
    // ルートシグネチャセット
    void SetRootSignature();
    // ビューポートセット
    void SetViewports();
    // シザー矩形セット
    void SetScissorRects();
    // プリミティブトポロジーセット
    void SetPremitiveTopology();
    // 頂点バッファのセット
    void SetVertexBuffers();
    // 頂点バッファのセット
    void SetIndexBuffer(); 
    // 描画命令セット
    void SetDrawInstanced();

    // レンダーターゲットの準備
    void PrepareRenderTarget();
    



    // バッファオブジェクト
    ComPtr<ID3D12Resource> _vertexBuffer;
    ComPtr<ID3D12Resource> _indexBuffer;

    // 頂点オブジェクト
    std::vector<std::shared_ptr<Object>> _objects;
    HRESULT CreateVertexSets();
    
    // 描画オブジェクト
    std::shared_ptr<Draw> _draw; 

    HRESULT CreateDrawObject();

    void ChangeRTVBarrierToRenderTarget(ID3D12Resource* rtv);
    void ChangeRTVBarrierToPresent     (ID3D12Resource* rtv);

    void SetRenderTarget  (D3D12_CPU_DESCRIPTOR_HANDLE handle);
    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);
    
    D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
    D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();

    void ExecuteDraw();

    void ExecuteCommand();
    void ResetCommand();

    void WaitProcessWithFence();


    
    



public:
    DX12(HWND hwnd);
    ~DX12();

    bool CreateDX12Object();
    void ExecuteDX12();
};