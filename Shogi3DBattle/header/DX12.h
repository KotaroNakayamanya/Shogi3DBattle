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
#include"HeapArg.h"
#include"PipelineArg.h"

class Vertex;
class Shader;
class Draw;
class Texture;
class Const;
class Object;
class Heap;
class RootSignature;
class Pipeline;

class DX12
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    HWND _hwnd; // ウインドウハンドル

    const int _buffNum = 2; // 描画に使用する画面数


    ComPtr<ID3D12Device>  _device;      // Direct3Dデバイス
    ComPtr<IDXGIFactory6> _dxgiFactory; // DXGIファクトリ

    // パイプラインオブジェクト
    std::shared_ptr<Pipeline> _pipeline;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout; // インプットレイアウト


    HRESULT CreateDevice();  // Direct3Dデバイス作成
    HRESULT CreateFactory(); // DXGIファクトリ作成
    ComPtr<IDXGIAdapter> GetUsingAdapter(); // 使用するアダプターを取得
    std::vector<ComPtr<IDXGIAdapter>> GetCanUseAdapters(); // 使用可能なアダプターを取得

    VertexArg::GetCreateVertexObjArg GetCreateVertexObjArg();

    // ルートシグネチャオブジェクト
    std::shared_ptr<RootSignature> _rootSignature;
    HRESULT CreateRootSignatureObj(); // ルートシグネチャオブジェクト作成


    HRESULT CreatePipelineState(); // パイプラインステート作成
    PipelineArg::CreatePipelineStateArg GetCreatePipelineStateArg(); // パイプラインステート作成用引数

    DXGI_SAMPLE_DESC GetSampleDesc();                          // サンプリングディスクリプタ
  

 


    // 頂点オブジェクト
    std::shared_ptr<Vertex> _vertex;
    HRESULT CreateVertexObj();

    // コンスタンとオブジェクト
    std::shared_ptr<Const> _const;
    HRESULT CreateConstObj();

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

    // ヒープオブジェクト
    std::shared_ptr<Heap> _heap;
    HRESULT CreateHeapObj(); // ヒープオブジェクト作成
    HeapArg::CreateHeapArg GetCreateHeapArg(); // ヒープ作成用引数

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