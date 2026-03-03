#include"DX12.h"

#include<D3Dcompiler.h>
#include<algorithm>
#include<string>
#include<cassert>

#include"Draw.h"
#include"Object.h"

#include"VertexStruct.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

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
bool DX12::CreateDX12Object()
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
    if (FAILED(CreateDrawObject()))
    {
        assert(false); return false;
    }

    // 頂点集合作成
    if (FAILED(CreateVertexSets()))
    {
        assert(false); return false;
    }
    // 頂点バッファ作成
    if (FAILED(CreateVertexBuffer()))
    {
        assert(false); return false;
    }
    // バッファに頂点をマップ
    if (FAILED(MapVertexToBuffer()))
    {
        assert(false); return false;
    }
    // インデックスバッファ作成
    if (FAILED(CreateIndexBuffer()))
    {
        assert(false); return false;
    }
    // バッファにインデックスをマップ
    if (FAILED(MapIndexToBuffer()))
    {
        assert(false); return false;
    }

    // テクスチャバッファ作成
    //if (FAILED(CreateTextureBuffer()))
    //{
    //    assert(false); return false;
    //}

    // シェーダーファイル読み込み
    if (FAILED(LoadShaderFile()))
    {
        assert(false); return false;
    }

    // ルートシグネチャ作成
    if (FAILED(CreateRootSignature()))
    {
        assert(false); return false;
    }

    // （グラフィックス）パイプラインステート作成
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

    for(auto adapter : canUseAdapters)
    {
        // アダプター名取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapter->GetDesc(&adapterDesc);
        std::wstring str = adapterDesc.Description;


        for (auto adapterName : adapterNames)
        {
            if (str.find(adapterName) != std::string::npos)
                return adapter.Get();
        }
    }

    return canUseAdapters[0].Get();
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
        adapters.push_back(tmpAdapter.Get());
        i++;
    }

    return adapters;
}

// 描画オブジェクト作成（Drawクラス）
HRESULT DX12::CreateDrawObject()
{
    _draw.reset(new Draw(_bufferNum));

    DrawArgument::CreateDrawObjectArgument arg =
        GetCreateDrawObjectArgument();

    return _draw->CreateDrawObject(arg);
}

// 描画オブジェクト作成用引数
DrawArgument::CreateDrawObjectArgument DX12::GetCreateDrawObjectArgument()
{
    DrawArgument::CreateDrawObjectArgument arg = {};

    arg.device =
        _device.Get();
    arg.dxgiFactory =
        _dxgiFactory.Get();
    arg.hwnd =
        _hwnd;
    arg.commandQueueDesc =
        GetCommandQueueDesc();
    arg.swapChainDesc =
        GetSwapChainDesc();
    arg.rtvHeapDesc =
        GetRTVHeapDesc();

    return arg;
}

// コマンドキューディスクリプタ
D3D12_COMMAND_QUEUE_DESC DX12::GetCommandQueueDesc()
{
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type =    // コマンドリストタイプの種類
        D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = // アプリケーション優先度 通常
        D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = // タイムアウトなし
        D3D12_COMMAND_QUEUE_FLAG_NONE; 
    desc.NodeMask =
        0;

    return desc;
}

// スワップチェーンディスクリプタ
DXGI_SWAP_CHAIN_DESC1 DX12::GetSwapChainDesc()
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};

    desc.Width =
        1280;
    desc.Height =
        720;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo =
        false;
    desc.SampleDesc.Count =
        1;
    desc.SampleDesc.Quality =
        0;
    desc.BufferUsage =
        DXGI_USAGE_BACK_BUFFER;
    desc.BufferCount =
        _bufferNum;

    desc.Scaling =
        DXGI_SCALING_STRETCH;
    desc.SwapEffect =
        DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode =
        DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags =
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    return desc;
}

// RTVヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC DX12::GetRTVHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        _bufferNum;
    desc.Flags =
        D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return desc;
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

// 頂点バッファ作成
HRESULT DX12::CreateVertexBuffer()
{
    // 頂点ヒーププロパティ取得
    D3D12_HEAP_PROPERTIES heapProperty =
        GetHeapProperty();
    // リソースディスクリプタ取得
    D3D12_RESOURCE_DESC resourceDesc =
        GetResourceDesc();
    resourceDesc.Width =
        _objects[0]->GetVerticesCount() * _objects[0]->GetVerticesByte();

    return _device->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_vertexBuffer.ReleaseAndGetAddressOf()));

}

// 頂点ヒーププロパティ
D3D12_HEAP_PROPERTIES DX12::GetHeapProperty()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

// 
D3D12_RESOURCE_DESC DX12::GetResourceDesc()
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Height =
        1;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count =
        1;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    return desc;
}

// インデックスバッファ作成
HRESULT DX12::CreateIndexBuffer()
{
    // 頂点ヒーププロパティ取得
    D3D12_HEAP_PROPERTIES heapProperty =
        GetHeapProperty();
    // リソースディスクリプタ取得
    D3D12_RESOURCE_DESC resourceDesc =
        GetResourceDesc();
    resourceDesc.Width = _objects[0]->GetIndicesByte();

    return _device->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_indexBuffer.ReleaseAndGetAddressOf()));

}

// バッファに頂点をマップ
HRESULT DX12::MapVertexToBuffer()
{
    std::shared_ptr<VertexStruct::Vertex> vertexMap;

    HRESULT result = _vertexBuffer->Map(
        0, nullptr, (void**)&vertexMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto vertices = _objects[0]->GetVerticesPtr();

    std::copy(vertices.begin(), vertices.end(), vertexMap.get());

    _vertexBuffer->Unmap(0, nullptr);

    return S_OK;
}

// バッファにインデックスをマップ
HRESULT DX12::MapIndexToBuffer()
{
    std::shared_ptr<unsigned short> idxMap;

    HRESULT result = _indexBuffer->Map(
        0, nullptr, (void**)&idxMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto indices = _objects[0]->GetIndicesPtr();
    
    std::copy(indices.begin(), indices.end(), idxMap.get());

    _indexBuffer->Unmap(0, nullptr);
    
    return S_OK;
}

// シェーダーファイルをロード
HRESULT DX12::LoadShaderFile()
{
    if (FAILED(LoadVertexShaderFile()))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(LoadPixelShaderFile()))
    {
        assert(false); return E_FAIL;
    }

    return S_OK;
}

HRESULT DX12::LoadVertexShaderFile()
{
    return D3DCompileFromFile(
        L"shader/VertexShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VShader",
        "vs_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        _vertexShaderBlob.ReleaseAndGetAddressOf(),
        _errorBlob       .ReleaseAndGetAddressOf());
}

HRESULT DX12::LoadPixelShaderFile()
{
    return D3DCompileFromFile(
        L"shader/PixelShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PShader",
        "ps_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        _pixelShaderBlob.ReleaseAndGetAddressOf(),
        _errorBlob      .ReleaseAndGetAddressOf());
}

// ルートシグネチャ作成
HRESULT DX12::CreateRootSignature()
{
    ComPtr<ID3DBlob> _rootSignatureBlob =
        GetRootSignatureBlob();

    return _device->CreateRootSignature(
        0,
        _rootSignatureBlob->GetBufferPointer(),
        _rootSignatureBlob->GetBufferSize(),
        IID_PPV_ARGS(_rootSignature.ReleaseAndGetAddressOf()));
}

 // ルートシグネチャBlob取得
ComPtr<ID3DBlob> DX12::GetRootSignatureBlob()
{
    ComPtr<ID3DBlob> rootSignatureBlob;

    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc =
        GetRootSignatureDesc();

    D3D12SerializeRootSignature(
        &rootSignatureDesc,
        D3D_ROOT_SIGNATURE_VERSION_1_0,
        rootSignatureBlob.ReleaseAndGetAddressOf(),
        _errorBlob.       ReleaseAndGetAddressOf());

    return rootSignatureBlob.Get();
}

// ルートシグネチャディスクリプタ
D3D12_ROOT_SIGNATURE_DESC DX12::GetRootSignatureDesc()
{
    D3D12_ROOT_SIGNATURE_DESC desc = {};

    desc.Flags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    return desc;
}





// パイプラインステート作成
HRESULT DX12::CreatePipelineState()
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc =
        GetPipelineStateDesc();

    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
    inputLayout.resize(2);
    inputLayout[0] =
    { // 頂点レイアウト
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[1] = 
    { // uv
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };

    D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
    inputLayoutDesc.pInputElementDescs =
        inputLayout.data();
    inputLayoutDesc.NumElements =
        inputLayout.size();
    
    desc.InputLayout = inputLayoutDesc;

    return _device->CreateGraphicsPipelineState(
        &desc,
        IID_PPV_ARGS(_pipelineState.ReleaseAndGetAddressOf()));
}

D3D12_GRAPHICS_PIPELINE_STATE_DESC DX12::GetPipelineStateDesc()
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};   
    
    desc.pRootSignature =
        _rootSignature.Get();
    desc.VS =
        GetVertexShaderDesc();
    desc.PS =
        GetPixelShaderDesc();
    desc.SampleMask =
        D3D12_DEFAULT_SAMPLE_MASK;
    desc.BlendState =
        GetBlendStateDesc();
    desc.RasterizerState =
        GetRasterizerDesc();
    desc.IBStripCutValue =
        D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    desc.PrimitiveTopologyType =
        D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    desc.NumRenderTargets =
        1;
    desc.RTVFormats[0] =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc =
        GetSampleDesc();


    return desc;
}

D3D12_INPUT_LAYOUT_DESC DX12::GetInputLayoutDesc(
    std::vector<D3D12_INPUT_ELEMENT_DESC>* inputLayout)
{
    D3D12_INPUT_LAYOUT_DESC desc = {};

    desc.pInputElementDescs =
        inputLayout->data();
    desc.NumElements =
        inputLayout->size();
 
    return desc;
}

D3D12_SHADER_BYTECODE DX12::GetVertexShaderDesc()
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        _vertexShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        _vertexShaderBlob->GetBufferSize();

    return desc;
}

D3D12_SHADER_BYTECODE DX12::GetPixelShaderDesc()
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        _pixelShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        _pixelShaderBlob->GetBufferSize();

    return desc;
}

D3D12_BLEND_DESC DX12::GetBlendStateDesc()
{
    D3D12_BLEND_DESC desc = {};

    desc.AlphaToCoverageEnable =
        false;
    desc.IndependentBlendEnable =
        false;
    desc.RenderTarget[0] = 
        GetRenderTargetBlendDesc();

    return desc;
}

D3D12_RENDER_TARGET_BLEND_DESC DX12::GetRenderTargetBlendDesc()
{
    D3D12_RENDER_TARGET_BLEND_DESC desc = {};

    desc.BlendEnable =
        false;
    desc.LogicOpEnable =
        false;
    desc.RenderTargetWriteMask =
        D3D12_COLOR_WRITE_ENABLE_ALL;

    return desc;
}

D3D12_RASTERIZER_DESC DX12::GetRasterizerDesc()
{
    D3D12_RASTERIZER_DESC desc = {};

    desc.MultisampleEnable =
        false;
    desc.CullMode =
        D3D12_CULL_MODE_NONE;
    desc.FillMode =
        D3D12_FILL_MODE_SOLID;
    desc.DepthClipEnable =
        true;

    return desc;
}

DXGI_SAMPLE_DESC DX12::GetSampleDesc()
{
    DXGI_SAMPLE_DESC desc = {};

    desc.Count   = 1; // サンプリング数
    desc.Quality = 0; // クオリティ（0は最低）

    return desc;
}




// コマンド実行
void DX12::ExecuteDX12()
{
    // レンダーターゲットの準備をする
    PrepareRenderTarget();

    // コマンドセット
    SetCommand();

    // 描画実行
    ExecuteDraw();

    return;
}

// レンダーターゲットの準備（Drawクラス）
void DX12::PrepareRenderTarget()
{
    DrawArgument::PrepareRenderTargetArgument arg =
        GetPrepareRenderTargetArgument();
        
    //_draw->PrepareRenderTarget(rtvOffset);
    _draw->PrepareRenderTarget(arg);
}

// レンダーターゲット準備用引数
DrawArgument::PrepareRenderTargetArgument DX12::GetPrepareRenderTargetArgument()
{
    DrawArgument::PrepareRenderTargetArgument arg = {};

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
    DrawArgument::SetCommandArgument arg =
        GetSetCommandArgument();

    _draw->SetCommand(arg);
}

// コマンドセット用引数
DrawArgument::SetCommandArgument DX12::GetSetCommandArgument()
{
    DrawArgument::SetCommandArgument arg = {};

    arg.pipelineState =
        _pipelineState.Get();
    arg.rootSignature =
        _rootSignature.Get();
    arg.viewport =
        GetViewports();
    arg.scissorRect =
        GetScissorRects();
    arg.topology =
        D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    arg.vertexBufferView =
        GetVertexBufferView();
    arg.indexBufferView =
        GetIndexBufferView();
    arg.vertexCount
        = _objects[0]->GetIndicesCount();
    arg.objectCount
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
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertexBufferView()
{
    D3D12_VERTEX_BUFFER_VIEW view;

    UINT vertexByte = _objects[0]->GetVerticesByte();
    UINT verticesByte = vertexByte * _objects[0]->GetVerticesCount();

    view.BufferLocation =
        _vertexBuffer->GetGPUVirtualAddress();
    view.SizeInBytes =
        verticesByte; // 注意
    view.StrideInBytes =
        vertexByte; // 注意

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIndexBufferView()
{
    D3D12_INDEX_BUFFER_VIEW view;

    UINT indicesByte = _objects[0]->GetIndicesByte();

    view.BufferLocation =
        _indexBuffer->GetGPUVirtualAddress();
    view.Format =
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =
        indicesByte;

    return view;
}

// 描画実行（Drawクラス）
void DX12::ExecuteDraw()
{
    DrawArgument::ExecuteDrawArgument arg =
        GetExecuteDrawArgument();
        
    _draw->ExecuteDraw(arg);
}

// コマンド実行用引数
DrawArgument::ExecuteDrawArgument DX12::GetExecuteDrawArgument()
{
    DrawArgument::ExecuteDrawArgument arg = {};

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