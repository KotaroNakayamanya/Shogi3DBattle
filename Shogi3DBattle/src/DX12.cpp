#include"DX12.h"

#include<algorithm>
#include<cassert>

#include"DXGIFactory.h"
#include"Adapter.h"
#include"Device.h"
#include"Shader.h"
#include"Texture.h"
#include"Draw.h"
#include"Vertex.h"
#include"Object.h"
#include"Const.h"
#include"CSUHeap.h"
#include"RootSignature.h"
#include"Pipeline.h"

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    // デバッグ有効化
    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer = nullptr;

        D3D12GetDebugInterface(
            IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

        debugLayer->EnableDebugLayer();
    }
}


// DirectX12初期設定
bool DX12::CreateDX12Obj()
{
    // DXGIファクトリーオブジェクト作成
    if (FAILED(CreateDXGIFactoryObj()))
    {
        assert(false); return false;
    }
    // アダプターオブジェクト作成
    if (FAILED(CreateAdapterObj()))
    {
        assert(false); return false;
    }
    // デバイスオブジェクト作成
    if (FAILED(CreateDeviceObj()))
    {
        assert(false); return false;
    }

    // 描画オブジェクト作成
    if (FAILED(CreateDrawObj()))
    {
        assert(false); return false;
    }

    // シェーダーバイナリオブジェクト作成
    if (FAILED(CreateShaderObj()))
    {
        assert(false); return false;
    }

    // 頂点集合作成
    if (FAILED(CreateVertexSets()))
    {
        assert(false); return false;
    }

    // 頂点オブジェクト作成
    if (FAILED(CreateVertexObj()))
    {
        assert(false); return false;
    }

    // テクスチャオブジェクト作成
    if (FAILED(CreateTextureObj()))
    {
        assert(false); return false;
    }
    // コンスタントオブジェクト作成
    if (FAILED(CreateConstObj()))
    {
        assert(false); return false;
    }
    // ヒープオブジェクト作成
    if (FAILED(CreateHeapObj()))
    {
        assert(false); return false;
    }

    // ルートシグネチャオブジェクト作成
    if (FAILED(CreateRootSignatureObj()))
    {
        assert(false); return false;
    }
    // パイプラインオブジェクト作成
    if (FAILED(CreatePipelineObj()))
    {
        assert(false); return false;
    }


    return true;
}

// DXGIファクトリオブジェクト作成
HRESULT DX12::CreateDXGIFactoryObj()
{
    _dxgiFactory = std::make_unique<DXGIFactory>();

    return _dxgiFactory->CreateDXGIFactory();
}

// アダプターオブジェクト作成
HRESULT DX12::CreateAdapterObj()
{
    _adapter = std::make_unique<Adapter>();

    return _adapter->CreateAdapter(_dxgiFactory->GetDXGIFactory());
}

// デバイスオブジェクト作成
HRESULT DX12::CreateDeviceObj()
{
    _device = std::make_unique<Device>();
    
    return _device->CreateDevice(_adapter->GetAdapter());
}

// 描画オブジェクト作成（Drawクラス）
HRESULT DX12::CreateDrawObj()
{
    _draw = std::make_unique<Draw>(_buffNum);

    DrawArg::CreateDrawObjArg arg =
        GetCreateDrawObjArg();

    return _draw->CreateDrawObj(arg);
}

// 描画オブジェクト作成用引数
DrawArg::CreateDrawObjArg DX12::GetCreateDrawObjArg()
{
    DrawArg::CreateDrawObjArg arg = {};

    arg.device =
        _device->GetDevice();
    arg.dxgiFactory =
        _dxgiFactory->GetDXGIFactory();
    arg.hwnd =
        _hwnd;

    return arg;
}

// ヒープ作成
HRESULT DX12::CreateHeapObj()
{
    _heap = std::make_unique<CSUHeap>();

    HeapArg::CreateCSUHeapArg arg = GetCreateCSUHeapArg();
    return _heap->CreateHeap(arg);
}

// ヒープ作成用引数
HeapArg::CreateCSUHeapArg DX12::GetCreateCSUHeapArg()
{
    HeapArg::CreateCSUHeapArg arg = {};

    arg.device = _device->GetDevice();
    arg.buff1 = _const->GetBuff();
    arg.buff2 = _texture->GetBuff();
  //arg.buff3 = nullptr;

    return arg;
}

// 頂点集合作成
HRESULT DX12::CreateVertexSets()
{

    /*std::for_each(_objects.begin(), _objects.end(),
        [](std::unique_ptr<Object>& object)
        {
            object = std::make_unique<Object>();
        });*/
    _object = std::make_unique<Object>();

    return S_OK;
}

// テクスチャオブジェクト作成
HRESULT DX12::CreateTextureObj()
{
    _texture = std::make_unique<Texture>();

    TextureArg::CreateTextureObjArg arg =
        GetCreateTextureObjArg();
    
    return _texture->CreateTextureObj(arg);
}

// コンスタントオブジェクト作成
HRESULT DX12::CreateConstObj()
{
    _const = std::make_unique<Const>();

    return _const->CreateConstObj(_device->GetDevice());
}

// テクスチャオブジェクト作成用引数
TextureArg::CreateTextureObjArg DX12::GetCreateTextureObjArg()
{
    TextureArg::CreateTextureObjArg arg = {};

    arg.device = _device->GetDevice();
    arg.sampleDesc = GetSampleDesc();

    return arg;
}

// サンプリングディスクリプタ
DXGI_SAMPLE_DESC DX12::GetSampleDesc()
{
    DXGI_SAMPLE_DESC desc = {};

    desc.Count   = 1; // サンプリング数
    desc.Quality = 0; // クオリティ（0は最低）

    return desc;
}

// 頂点オブジェクト作成
HRESULT DX12::CreateVertexObj()
{
    _vertex = std::make_unique<Vertex>();

    VertexArg::GetCreateVertexObjArg arg =
        GetCreateVertexObjArg();

    return _vertex->CreateVertexObj(arg);
}

// 頂点オブジェクト作成用関数
VertexArg::GetCreateVertexObjArg DX12::GetCreateVertexObjArg()
{
    VertexArg::GetCreateVertexObjArg arg = {};

    arg.device = _device->GetDevice();
    arg.vertexByte = _object->GetVerticesCount() * _object->GetVerticesByte();
    arg.vertexPtr = _object->GetVerticesPtr();
    arg.indexByte = _object->GetIndicesByte();
    arg.indexPtr = _object->GetIndicesPtr();

    return arg;
}

// シェーダーバイナリ作成
HRESULT DX12::CreateShaderObj()
{
    _shader = std::make_unique<Shader>();
    return _shader->CreateShaderBlob();
}

//// ルートシグネチャオブジェクト作成
HRESULT DX12::CreateRootSignatureObj()
{
    _rootSignature = std::make_unique<RootSignature>();

    return _rootSignature->CreateRootSignatureObj(_device->GetDevice());
}





// パイプラインオブジェクト作成
HRESULT DX12::CreatePipelineObj()
{
    _pipeline = std::make_unique<Pipeline>();

    PipelineArg::CreatePipelineStateArg arg =
        GetCreatePipelineObjArg();

    return _pipeline->CreatePipelineState(arg);
}

PipelineArg::CreatePipelineStateArg DX12::GetCreatePipelineObjArg()
{
    PipelineArg::CreatePipelineStateArg arg = {};

    arg.device = _device->GetDevice();
    arg.rootSignature = _rootSignature->GetRootSignature();
    arg.vertexShaderBlob = _shader->GetVertexShaderBlob();
    arg.pixelShaderBlob  = _shader->GetPixelShaderBlob();
    arg.sampleDesc = GetSampleDesc();

    return arg;
}




// コマンド実行
void DX12::ExeDX12()
{
    // レンダーターゲットの準備をする
     PrepareRenderTarget();

    // コマンドセット
    SetCommand();

    // 描画実行
    ExeDraw();

    return;
}

// レンダーターゲットの準備（Drawクラス）
void DX12::PrepareRenderTarget()
{
    DrawArg::PrepareRenderTargetArg arg =
        GetPrepareRenderTargetArg();
        
    _draw->PrepareRenderTarget(arg);
}

// レンダーターゲット準備用引数
DrawArg::PrepareRenderTargetArg DX12::GetPrepareRenderTargetArg()
{
    DrawArg::PrepareRenderTargetArg arg = {};

    arg.resourceBarrier =
        GetResourceBarrier();
    arg.rtvOffset = 
        _device->GetDevice()->GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE_RTV); 
        

    return arg;
}

// リソースバリア
D3D12_RESOURCE_BARRIER DX12::GetResourceBarrier()
{
    D3D12_RESOURCE_BARRIER desc;

    desc.Type =
        D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    desc.Flags =
        D3D12_RESOURCE_BARRIER_FLAG_NONE;
    desc.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    return desc;  
}

// コマンドセット（Drawクラス）
void DX12::SetCommand()
{
    DrawArg::SetCommandArg arg =
        GetSetCommandArg();

    _draw->SetCommand(arg);

}

// コマンドセット用引数
DrawArg::SetCommandArg DX12::GetSetCommandArg()
{
    DrawArg::SetCommandArg arg = {};

    arg.pipelineState =
        _pipeline->GetPipelineState();
    arg.rootSignature =
        _rootSignature->GetRootSignature();
    arg.heap
        = _heap->GetHeap();;
    arg.offset =
        _device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    arg.viewport =
        GetViewports();
    arg.scissorRect =
        GetScissorRects();
    arg.topology =
        D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    arg.vertexBuffView =
        GetVertexBuffView();
    arg.indexBuffView =
        GetIndexBuffView();
    arg.vertexCount
        = _object->GetIndicesCount();
    arg.objCount
        = 1;

    return arg;
}

// ビューポートセット
D3D12_VIEWPORT DX12::GetViewports()
{
    D3D12_VIEWPORT viewport = {};

    viewport.Width    = 1280;
    viewport.Height   = 720;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MaxDepth = 1.0f; // 深度最大値
    viewport.MinDepth = 0.0f; // 深度最小値

    return viewport;
}

// シザー矩形セット
D3D12_RECT DX12::GetScissorRects()
{
    D3D12_RECT scissorRect = {};

    scissorRect.left = 0;
    scissorRect.right = 1280;
    scissorRect.top = 0;
    scissorRect.bottom = 720;
    
    return scissorRect;
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertexBuffView()
{
    D3D12_VERTEX_BUFFER_VIEW view;

    ComPtr<ID3D12Resource> vertexBuff =
        _vertex->GetVertexBuff();

    UINT vertexByte = _object->GetVerticesByte();
    UINT verticesByte = vertexByte * _object->GetVerticesCount();

    view.BufferLocation =
        vertexBuff->GetGPUVirtualAddress();
    view.SizeInBytes =
        verticesByte; // 注意
    view.StrideInBytes =
        vertexByte; // 注意

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIndexBuffView()
{
    D3D12_INDEX_BUFFER_VIEW view;

    ComPtr<ID3D12Resource> indexBuff =
        _vertex->GetIndexBuff();

    UINT indicesByte = _object->GetIndicesByte();

    view.BufferLocation =
        indexBuff->GetGPUVirtualAddress();
    view.Format =
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =
        indicesByte;

    return view;
}

// 描画実行（Drawクラス）
void DX12::ExeDraw()
{
    DrawArg::ExeDrawArg arg =
        GetExeDrawArg();
        
    _draw->ExeDraw(arg);
}

// コマンド実行用引数
DrawArg::ExeDrawArg DX12::GetExeDrawArg()
{
    DrawArg::ExeDrawArg arg = {};

    arg.resourceBarrier =
        GetResourceBarrier();

    return arg;
}




DX12::DX12(HWND hwnd) : DX12()
{
    _hwnd = hwnd;
}

DX12::DX12() {
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif
}

DX12::~DX12(){}