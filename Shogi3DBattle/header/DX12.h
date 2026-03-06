#pragma once

#include<memory>

#include"DrawArg.h"
#include"TextureArg.h"
#include"VertexArg.h"
#include"HeapArg.h"
#include"PipelineArg.h"

class DXGIFactory;
class Adapter;
class Device;
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
private:
    HWND _hwnd; // ウインドウハンドル

    const int _buffNum = 2; // 描画に使用する画面数


    std::unique_ptr<DXGIFactory> _dxgiFactory; // DXGIファクトリーオブジェクト
    HRESULT CreateDXGIFactoryObj();            // DXGIファクトリ作成

    std::unique_ptr<Adapter> _adapter; // アダプターオブジェクト
    HRESULT CreateAdapterObj();        // アダプターオブジェクト作成

    std::unique_ptr<Device> _device; // Direct3Dデバイスオブジェクト
    HRESULT CreateDeviceObj();       // Direct3Dデバイスオブジェクト作成

    std::unique_ptr<Draw> _draw; // 描画オブジェクト
    HRESULT CreateDrawObj();     // 描画オブジェクト作成


    std::unique_ptr<Shader> _shader; // シェーダーオブジェクト
    HRESULT CreateShaderObj();       // シェーダーオブジェクト作成

    std::unique_ptr<Vertex> _vertex; // 頂点オブジェクト
    HRESULT CreateVertexObj();       // 頂点オブジェクト作成
    VertexArg::GetCreateVertexObjArg // 頂点オブジェクト作成用引数
        GetCreateVertexObjArg();

    std::unique_ptr<RootSignature> _rootSignature; // ルートシグネチャオブジェクト
    HRESULT CreateRootSignatureObj();              // ルートシグネチャオブジェクト作成

    std::unique_ptr<Pipeline> _pipeline; // パイプラインオブジェクト
    HRESULT CreatePipelineObj();         // パイプラインオブジェクト作成
    PipelineArg::CreatePipelineStateArg  // パイプラインオブジェクト作成用引数
        GetCreatePipelineObjArg(); 

    std::unique_ptr<Texture> _texture; // テクスチャオブジェクト
    HRESULT CreateTextureObj();        // テクスチャオブジェクト作成
    TextureArg::CreateTextureObjArg    // テクスチャオブジェクト作成用引数
        GetCreateTextureObjArg();

    std::unique_ptr<Const> _const; // コンスタントオブジェクト
    HRESULT CreateConstObj();      // コンスタントオブジェクト作成

    std::unique_ptr<Heap> _heap; // ヒープオブジェクト
    HRESULT CreateHeapObj();     // ヒープオブジェクト作成
    HeapArg::CreateHeapArg       // ヒープオブジェクト作成用引数
        GetCreateHeapObjArg();  

    DXGI_SAMPLE_DESC GetSampleDesc(); // サンプリングディスクリプタ
  
    // ビューポート
    D3D12_VIEWPORT GetViewports();
    // シザー矩形
    D3D12_RECT GetScissorRects();

    // レンダーターゲットの準備
    void PrepareRenderTarget();

    // コマンドセット
    void SetCommand();

    // 頂点オブジェクト
    std::unique_ptr<Object> _object;
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
    DrawArg::CreateDrawObjArg // 描画オブジェクト作成用引数
        GetCreateDrawObjArg();
    DrawArg::PrepareRenderTargetArg // レンダーターゲット準備用引数
        GetPrepareRenderTargetArg();
    DrawArg::SetCommandArg // コマンドセット用引数
        GetSetCommandArg();
    DrawArg::ExeDrawArg // コマンド実行用引数
        GetExeDrawArg();
    
public:
    bool CreateDX12Obj(); // DirectX12オブジェクト作成
    void ExeDX12(); // DirectX12実行処理

    DX12(HWND hwnd);
    DX12();
    ~DX12();
};