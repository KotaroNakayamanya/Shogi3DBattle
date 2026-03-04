#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<DirectXMath.h>
#include<memory>
#include<wrl.h>
#include<vector>
#include<array>

#include"DrawArg.h"
#include"TextureArg.h"
#include"VertexArg.h"

class Vertex;
class Shader;
class Draw;
class Texture;
class Object;

class DX12
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    HWND _hwnd; // ウインドウハンドル

    const int _buffNum = 2; // 描画に使用する画面数


    ComPtr<ID3D12Device>  _device;      // Direct3Dデバイス
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリ

    

    ComPtr<ID3D12RootSignature> _rootSignature; // ルートシグネチャ
    ComPtr<ID3D12PipelineState> _pipelineState; //パイプラインステート

    std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout; // インプットレイアウト


    HRESULT CreateDevice();  // Direct3Dデバイス作成
    HRESULT CreateFactory(); // DXGIファクトリ作成
    ComPtr<IDXGIAdapter> GetUsingAdapter(); // 使用するアダプターを取得
    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプターを取得

    VertexArg::GetCreateVertexObjArg GetCreateVertexObjArg();

    HRESULT CreateRootSignature(); // ルートシグネチャ作成
    ComPtr<ID3DBlob> GetRootSignatureBlob(); // ルートシグネチャBlob取得
    HRESULT CreatePipelineState(); // パイプラインステート作成
  

    D3D12_ROOT_PARAMETER GetRootParam(); // ルートパラメータ
    D3D12_ROOT_DESCRIPTOR_TABLE GetDescTable(); // ディスクリプタテーブル
    D3D12_DESCRIPTOR_RANGE GetDescRange(); // ディスクリプタレンジ
    D3D12_STATIC_SAMPLER_DESC GetSamplerDesc(); // サンプラーディスクリプタ

    // ディスクリプタで使用されたメモリ開放
    void DeleteRootSignatureDescMemory(D3D12_ROOT_SIGNATURE_DESC* desc);


    // ヒープ
    D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc(); // RTVヒープディスクリプタ


    // 頂点オブジェクト
    std::shared_ptr<Vertex> _vertex;
    HRESULT CreateVertexObj();
    
    


    

    // 描画オブジェクト
    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc(); // コマンドキューディスクリプタ
    DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc(); // スワップチェーンディスクリプタ
 

    // ルートシグネチャ
    D3D12_ROOT_SIGNATURE_DESC GetRootSignatureDesc(); // ルートシグネチャディスクリプタ


    // パイプラインステート
    D3D12_GRAPHICS_PIPELINE_STATE_DESC GetPipelineStateDesc(); // パイプラインステートディスクリプタ
    D3D12_SHADER_BYTECODE GetVertexShaderDesc();               // 頂点シェーダーディスクリプタ
    D3D12_SHADER_BYTECODE GetPixelShaderDesc();                // ピクセルシェーダーディスクリプタ
    D3D12_BLEND_DESC GetBlendStateDesc();                      // ブレンドステートディスクリプタ
    D3D12_RENDER_TARGET_BLEND_DESC GetRenderTargetBlendDesc(); // レンダーターゲットブレンドディスクリプタ
    D3D12_RASTERIZER_DESC GetRasterizerDesc();                 // ラスタライザディスクリプタ
    D3D12_INPUT_LAYOUT_DESC GetInputLayoutDesc(                // インプットレイアウトディスクリプタ
        std::vector<D3D12_INPUT_ELEMENT_DESC>* inputLayout);
    DXGI_SAMPLE_DESC GetSampleDesc();                          // サンプリングディスクリプタ

    


    // ビューポート
    D3D12_VIEWPORT GetViewports();
    // シザー矩形
    D3D12_RECT GetScissorRects();

    // レンダーターゲットの準備
    void PrepareRenderTarget();

    // コマンドセット
    void SetCommand();
    
    // テクスチャオブジェクト
    std::shared_ptr<Texture> _texture;
    HRESULT CreateTextureObj(); // テクスチャオブジェクト作成
    TextureArg::CreateTextureObjArg // テクスチャオブジェクト作成用引数
        GetCreateTextureObjArg();

    // 頂点オブジェクト
    std::vector<std::shared_ptr<Object>> _objects;
    HRESULT CreateVertexSets();
    
    

   
    
    // コマンドセット
    D3D12_VERTEX_BUFFER_VIEW GetVertexBuffView();
    D3D12_INDEX_BUFFER_VIEW GetIndexBuffView();


    void ExeDraw();
    void ResetCommand();
    void WaitProcessWithFence();

    // リソースバリア
    D3D12_RESOURCE_BARRIER GetResourceBarrier();

    // 描画オブジェクト
    std::shared_ptr<Draw> _draw; 
    HRESULT CreateDrawObj(); // 描画オブジェクト作成
    DrawArg::CreateDrawObjArg // 描画オブジェクト作成用引数
        GetCreateDrawObjArg();
    DrawArg::PrepareRenderTargetArg // レンダーターゲット準備用引数
        GetPrepareRenderTargetArg();
    DrawArg::SetCommandArg // コマンドセット用引数
        GetSetCommandArg();
    DrawArg::ExeDrawArg // コマンド実行用引数
        GetExeDrawArg();
    

    // シェーダーオブジェクト
    std::shared_ptr<Shader> _shader;
    HRESULT CreateShaderBlob(); // シェーダーバイナリ作成



public:
    bool CreateDX12Obj();
    void ExeDX12();

    DX12(HWND hwnd);
    ~DX12();
};