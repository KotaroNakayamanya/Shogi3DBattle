#include"DX12.h"

#include<D3Dcompiler.h>
#include<algorithm>
#include<string>
#include<cassert>

#include"Shader.h"
#include"Texture.h"
#include"Draw.h"
#include"Vertex.h"
#include"Object.h"
#include"Const.h"
#include"Heap.h"
#include"RootSignature.h"
#include"Pipeline.h"

#include"VertexStruct.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

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
    // DXGIファクトリー作成
    if (FAILED(CreateFactory()))
    {
        assert(false); return false;
    }
    // デバイス作成（GPU機能レベルに対応していなければ失敗）
    if (FAILED(CreateDevice()))
    {
        assert(false); return false;
    }
    // 描画オブジェクト作成
    if (FAILED(CreateDrawObj()))
    {
        assert(false); return false;
    }

    // シェーダーバイナリ作成
    if (FAILED(CreateShaderBlob()))
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

    // パイプラインステート作成
    if (FAILED(CreatePipelineState()))
    {
        assert(false); return false;
    }


    return true;
}

// DXGIファクトリ作成
HRESULT DX12::CreateFactory()
{
    HRESULT result;
    // デバッグモードのときは詳細を表示させるファクトリを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}


// デバイス作成
HRESULT DX12::CreateDevice()
{
    // GPU機能レベル一覧
    std::array<D3D_FEATURE_LEVEL, 5> featureLevels =
    {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };
    
    // 使用するアダプターを取得
    ComPtr<IDXGIAdapter> adapter =
        GetUsingAdapter();

    // GPU機能レベルの配列順にデバイス作成を試みる
    HRESULT result;
    std::find_if(featureLevels.begin(), featureLevels.end(),
        [this, &result, adapter](D3D_FEATURE_LEVEL featureLevel)
        {
            result = D3D12CreateDevice(
                adapter.Get(),
                featureLevel,
                IID_PPV_ARGS(_device.ReleaseAndGetAddressOf()));

            return result == S_OK; // 作成できたら戻る
        });

    return result;
}

// 使用するアダプターを取得
ComPtr<IDXGIAdapter> DX12::GetUsingAdapter()
{
    // アダプター一覧
    std::array<std::wstring, 3> adapterNames =
    {
        L"NVIDIA",
        L"AMD",
        L"Intel"
    };

    // 使用可能なアダプターを取得
    std::vector<ComPtr<IDXGIAdapter>> canUseAdapters =
        GetCanUseAdapters();

    for(auto& adapter : canUseAdapters)
    {
        // アダプター名取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapter->GetDesc(&adapterDesc);
        std::wstring str = adapterDesc.Description;


        for (auto& adapterName : adapterNames)
        {
            if (str.find(adapterName) != std::string::npos)
                return adapter;
        }
    }

    return canUseAdapters[0];
}

// 使用可能なアダプターを取得
std::vector<ComPtr<IDXGIAdapter>> DX12::GetCanUseAdapters()
{
    std::vector<ComPtr<IDXGIAdapter>> adapters;

    ComPtr<IDXGIAdapter> tmpAdapter;
    int i = 0;
    while (_dxgiFactory->EnumAdapters(i, tmpAdapter.ReleaseAndGetAddressOf())
           != DXGI_ERROR_NOT_FOUND)
    {
        adapters.push_back(tmpAdapter);
        i++;
    }

    return adapters;
}

// 描画オブジェクト作成（Drawクラス）
HRESULT DX12::CreateDrawObj()
{
    _draw = std::make_shared<Draw>(_buffNum);

    DrawArg::CreateDrawObjArg arg =
        GetCreateDrawObjArg();

    return _draw->CreateDrawObj(arg);
}

// 描画オブジェクト作成用引数
DrawArg::CreateDrawObjArg DX12::GetCreateDrawObjArg()
{
    DrawArg::CreateDrawObjArg arg = {};

    arg.device =
        _device.Get();
    arg.dxgiFactory =
        _dxgiFactory.Get();
    arg.hwnd =
        _hwnd;

    return arg;
}

// ヒープ作成
HRESULT DX12::CreateHeapObj()
{
    _heap = std::make_shared<Heap>();

    HeapArg::CreateHeapArg arg = GetCreateHeapArg();

    return _heap->CreateHeapObj(arg);
}

// ヒープ作成用引数
HeapArg::CreateHeapArg DX12::GetCreateHeapArg()
{
    HeapArg::CreateHeapArg arg = {};

    arg.device = _device.Get();
    arg.srvBuff = _texture->GetBuff();
    arg.cbvBuff = _const->GetBuff();

    return arg;
}

// 頂点集合作成
HRESULT DX12::CreateVertexSets()
{
    int objectNum = 1;
    _objects.resize(objectNum);

    std::for_each(_objects.begin(), _objects.end(),
        [](std::shared_ptr<Object>& object)
        {
            object.reset(new Object);
        });

    return S_OK;
}

// テクスチャオブジェクト作成
HRESULT DX12::CreateTextureObj()
{
    _texture = std::make_shared<Texture>();

    TextureArg::CreateTextureObjArg arg =
        GetCreateTextureObjArg();
    
    return _texture->CreateTextureObj(arg);
}

// コンスタントオブジェクト作成
HRESULT DX12::CreateConstObj()
{
    _const = std::make_shared<Const>();

    return _const->CreateConstObj(_device.Get());
}

// テクスチャオブジェクト作成用引数
TextureArg::CreateTextureObjArg DX12::GetCreateTextureObjArg()
{
    TextureArg::CreateTextureObjArg arg = {};

    arg.device = _device.Get();
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
    _vertex = std::make_shared<Vertex>();

    VertexArg::GetCreateVertexObjArg arg =
        GetCreateVertexObjArg();

    return _vertex->CreateVertexObj(arg);
}

// 頂点オブジェクト作成用関数
VertexArg::GetCreateVertexObjArg DX12::GetCreateVertexObjArg()
{
    VertexArg::GetCreateVertexObjArg arg = {};

    arg.device = _device.Get();
    arg.vertexByte = _objects[0]->GetVerticesCount() * _objects[0]->GetVerticesByte();
    arg.vertexPtr = _objects[0]->GetVerticesPtr();
    arg.indexByte = _objects[0]->GetIndicesByte();
    arg.indexPtr = _objects[0]->GetIndicesPtr();

    return arg;
}

// シェーダーバイナリ作成
HRESULT DX12::CreateShaderBlob()
{
    _shader = std::make_shared<Shader>();
    return _shader->CreateShaderBlob();
}

//// ルートシグネチャオブジェクト作成
HRESULT DX12::CreateRootSignatureObj()
{
    _rootSignature = std::make_shared<RootSignature>();

    return _rootSignature->CreateRootSignatureObj(_device.Get());
}





// パイプラインステート作成
HRESULT DX12::CreatePipelineState()
{
    _pipeline = std::make_shared<Pipeline>();

    PipelineArg::CreatePipelineStateArg arg =
        GetCreatePipelineStateArg();

    return _pipeline->CreatePipelineState(arg);
}

PipelineArg::CreatePipelineStateArg DX12::GetCreatePipelineStateArg()
{
    PipelineArg::CreatePipelineStateArg arg = {};

    arg.device = _device.Get();
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
        _device->GetDescriptorHandleIncrementSize(
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
        _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
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
        = _objects[0]->GetIndicesCount();
    arg.objCount
        = _objects.size();

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

    UINT vertexByte = _objects[0]->GetVerticesByte();
    UINT verticesByte = vertexByte * _objects[0]->GetVerticesCount();

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

    UINT indicesByte = _objects[0]->GetIndicesByte();

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




DX12::DX12(HWND hwnd)
{
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _hwnd = hwnd;
}

DX12::~DX12(){}