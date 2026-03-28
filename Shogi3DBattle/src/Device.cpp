#include"Device.h"
#include"DSBuffFactory.h"
#include"ConstBuffFactory.h"
#include"VertBuffFactory.h"
#include"IdxBuffFactory.h"
#include"TexBuffFactory.h"
#include"RenderTexBuffFactory.h"
#include"RTVHeapFactory.h"
#include"DSVHeapFactory.h"
#include"CSUHeapFactory.h"
#include"RTVFactory.h"
#include"DSVFactory.h"
#include"CBVFactory.h"
#include"SRVFactory.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// コマンドアロケータオブジェクト作成
HRESULT Device::CreateCmdAllocator(CmdAllocator* cmdAllocator)
{
    ComPtr<ID3D12CommandAllocator> cmdAllocatorCom;

    HRESULT result;
    result = _device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(cmdAllocatorCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    cmdAllocator->SetCmdAllocator(cmdAllocatorCom);
    return S_OK;
}

// コマンドリスト作成
HRESULT Device::CreateCmdList(CmdList* cmdList, CmdAllocator* cmdAllocator)
{
    ComPtr<ID3D12GraphicsCommandList> cmdListCom;

    HRESULT result;
    result = _device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        cmdAllocator->GetCmdAllocator(),
        nullptr,
        IID_PPV_ARGS(cmdListCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    cmdList->SetCmdList(cmdListCom);
    return S_OK;
}

// コマンドキュー作成
HRESULT Device::CreateCmdQueue(CmdQueue* cmdQueue)
{
    ComPtr<ID3D12CommandQueue> cmdQueueCom;

    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = GetCmdQueueDesc();

    HRESULT result;
    result = _device->CreateCommandQueue(
        &cmdQueueDesc,
        IID_PPV_ARGS(cmdQueueCom.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    cmdQueue->SetCmdQueue(cmdQueueCom);
    return S_OK;
}

// コマンドキューディスクリプタ
D3D12_COMMAND_QUEUE_DESC Device::GetCmdQueueDesc()
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




// フェンス作成
HRESULT Device::CreateFence(Fence* fence)
{
    return _device->CreateFence(
        fence->_fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(fence->_fence.ReleaseAndGetAddressOf()));
}




// バッファ作成
HRESULT Device::CreateBuff(Buff* buff, UINT width, UINT height, Buff::BuffType buffType)
{
    switch (buffType)
    {
    case Buff::DEPTH_STENCIL:
        _buffFactory.reset(new DSBuffFactory());
        break;

    case Buff::VERTEX:
        _buffFactory.reset(new VertBuffFactory());
        break;

    case Buff::INDEX:
        _buffFactory.reset(new IdxBuffFactory());
        break;

    case Buff::CONSTANT:
        _buffFactory.reset(new ConstBuffFactory());
         break;

    case Buff::TEXTURE:
        _buffFactory.reset(new TexBuffFactory());
        break;

    case Buff::RENDER_TEX:
        _buffFactory.reset(new RenderTexBuffFactory());
        break;

    default:
        return E_FAIL;
    }

    _buffFactory->CreateBuff(buff, width, height, _device.Get());
}

// ヒープ作成
HRESULT Device::CreateHeap(Heap* heap, UINT descNum, Heap::HeapType heapType)
{
    switch (heapType)
    {
    case Heap::RTV:
        _heapFactory.reset(new RTVHeapFactory());
        break;

    case Heap::DSV:
        _heapFactory.reset(new DSVHeapFactory());
        break;

    case Heap::CSU:
        _heapFactory.reset(new CSUHeapFactory());
        break;

    default:
        return E_FAIL;
    }

    return _heapFactory->CreateHeap(heap, descNum, _device.Get());
}

// ヒープ作成（CSU）
HRESULT Device::CreateCSUHeap(CSUHeap* csuHeap, UINT cbvNum, UINT srvNum, UINT uavNum, Heap::HeapType heapType)
{
    // CSUヒープ内訳取得
    csuHeap->SetCBVNum(cbvNum);
    csuHeap->SetSRVNum(srvNum);
    csuHeap->SetUAVNum(uavNum);

    return CreateHeap(csuHeap, cbvNum + srvNum + uavNum, heapType);
}

// ビュー作成
void Device::CreateView(Heap* heap, UINT i, Buff* buff, View::ViewType viewType)
{
    switch (viewType)
    {
    case View::RTV:
        _viewFactory.reset(new RTVFactory());
        break;

    case View::DSV:
        _viewFactory.reset(new DSVFactory());
        break;

    case View::CBV:
        _viewFactory.reset(new CBVFactory());
        break;

    case View::SRV:
        _viewFactory.reset(new SRVFactory());
        break;

    default:
        return;
    }

    _viewFactory->CreateView(heap, i, buff, _device.Get());
}

// ビュー作成（CSU系）
void Device::CreateCSUView(CSUHeap* csuHeap, UINT i, Buff* buff, View::ViewType viewType)
{
    UINT offset = 0;

    switch (viewType)
    {
    case View::CBV:
        offset = csuHeap->GetCBVStartIdx();
        break;

    case View::SRV:
        offset = csuHeap->GetSRVStartIdx();
        break;

    case View::UAV:
        offset = csuHeap->GetUAVStartIdx();
        break;

    default:
        return;
    }

    CreateView(csuHeap, offset + i, buff, viewType);
}




// 頂点シェーダバイナリ作成
HRESULT Device::CreateVShader(VShader* vShader)
{
    return D3DCompileFromFile(
        L"shader/VertexShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VShader",
        "vs_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        vShader->_vShader.ReleaseAndGetAddressOf(),
        nullptr);
}

// ピクセルシェーダー作成
HRESULT Device::CreatePShader(PShader* pShader)
{
    return D3DCompileFromFile(
        L"shader/PixelShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PShader",
        "ps_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        pShader->_pShader.ReleaseAndGetAddressOf(),
        nullptr);
}




// ルートシグネチャ作成
HRESULT Device::CreateRootSignature(RootSignature* rootSignature, CSUHeap* csuHeap)
{
    ComPtr<ID3DBlob> _rootSignatureBlob = GetRootSignatureBlob(csuHeap); // ルートシグネチャバイナリ作成

    return _device->CreateRootSignature(
        0,
        _rootSignatureBlob->GetBufferPointer(),
        _rootSignatureBlob->GetBufferSize(),
        IID_PPV_ARGS(rootSignature->_rootSignature.ReleaseAndGetAddressOf()));
}

// ルートシグネチャBlob取得
Microsoft::WRL::ComPtr<ID3DBlob> Device::GetRootSignatureBlob(CSUHeap* csuHeap)
{
    ComPtr<ID3DBlob> rootSignatureBlob;

    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc =
        GetRootSignatureDesc(csuHeap);

    D3D12SerializeRootSignature(
        &rootSignatureDesc,
        D3D_ROOT_SIGNATURE_VERSION_1_0,
        rootSignatureBlob.ReleaseAndGetAddressOf(),
        nullptr);

    // ディスクリプタで使用されたメモリ開放
    DeleteRootSignatureDescMemory(&rootSignatureDesc);

    return rootSignatureBlob;
}

// ルートシグネチャディスクリプタ
D3D12_ROOT_SIGNATURE_DESC Device::GetRootSignatureDesc(CSUHeap* csuHeap)
{
    D3D12_ROOT_SIGNATURE_DESC desc = {};

    UINT paramNum = 2;
    UINT samplerNum = 1;

    std::vector<D3D12_ROOT_PARAMETER>* rootParameterPtr =
        new std::vector<D3D12_ROOT_PARAMETER>;
    *rootParameterPtr = GetRootParams(paramNum, csuHeap);

    std::vector<D3D12_STATIC_SAMPLER_DESC>* samplerDescPtr =
        new std::vector<D3D12_STATIC_SAMPLER_DESC>;
    *samplerDescPtr = GetSamplerDescs(samplerNum);

    desc.Flags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    desc.pParameters =
        rootParameterPtr->data();
    desc.NumParameters =
        paramNum;
    desc.pStaticSamplers =
        samplerDescPtr->data();
    desc.NumStaticSamplers =
        samplerNum;

    return desc;
}

// ルートパラメータ
std::vector<D3D12_ROOT_PARAMETER> Device::GetRootParams(UINT paramNum, CSUHeap* csuHeap)
{
    std::vector<D3D12_ROOT_PARAMETER> descs = {};
    descs.resize(paramNum);

    // CBV ワールド行列
    descs[0].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[0].ShaderVisibility = // 頂点シェーダで利用可能
        D3D12_SHADER_VISIBILITY_VERTEX;
    descs[0].DescriptorTable =
        GetDescTable(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, csuHeap->GetCBVNum());

    // SRV
    descs[1].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[1].ShaderVisibility = // ピクセルシェーダで利用可能
        D3D12_SHADER_VISIBILITY_PIXEL;
    descs[1].DescriptorTable =
        GetDescTable(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, csuHeap->GetSRVNum());

    return descs;
}

// ディスクリプタテーブル
D3D12_ROOT_DESCRIPTOR_TABLE Device::GetDescTable(
    D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
    UINT descNum)
{
    D3D12_ROOT_DESCRIPTOR_TABLE desc = {};

    std::vector<D3D12_DESCRIPTOR_RANGE>* descRangePtr =
        new std::vector<D3D12_DESCRIPTOR_RANGE>;

    *descRangePtr = GetDescRanges(rangeType, descNum);

    desc.pDescriptorRanges =
        descRangePtr->data();
    desc.NumDescriptorRanges =
        1;

    return desc;
}

// ディスクリプタレンジ
std::vector<D3D12_DESCRIPTOR_RANGE> Device::GetDescRanges(
    D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
    UINT descNum)
{
    std::vector<D3D12_DESCRIPTOR_RANGE> descs = {};
    descs.resize(1);

    descs[0].RangeType = // タイプ
        rangeType;
    descs[0].NumDescriptors = // ディスクリプタ数
        descNum;
    descs[0].BaseShaderRegister = // スロット0
        0;
    descs[0].OffsetInDescriptorsFromTableStart =
        D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;


    return descs;
}

// サンプラーディスクリプタ
std::vector<D3D12_STATIC_SAMPLER_DESC> Device::GetSamplerDescs(UINT samplerNum)
{
    std::vector<D3D12_STATIC_SAMPLER_DESC> descs = {};
    descs.resize(samplerNum);


    descs[0].AddressU = // 横
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    descs[0].AddressV = // 縦
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    descs[0].AddressW = // 奥行き
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    descs[0].BorderColor =
        D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    descs[0].Filter = // 線形補完
        D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    descs[0].MaxLOD = // ミップマップ最大値
        D3D12_FLOAT32_MAX;
    descs[0].MinLOD = // ミップマップ最小値
        0.0f;
    descs[0].ShaderVisibility = // シェーダ確認範囲
        D3D12_SHADER_VISIBILITY_PIXEL;
    descs[0].ComparisonFunc =
        D3D12_COMPARISON_FUNC_NEVER;

    return descs;
}

// ルートシグネチャディスクリプタのメモリ解放
void Device::DeleteRootSignatureDescMemory(D3D12_ROOT_SIGNATURE_DESC* desc)
{
    UINT paramNum = desc->NumParameters;     // ルートパラメータ数
    for (UINT i = 0; i < paramNum; i++) // ルートパラメータごとのディスクリプタレンジを解放する
    {
        UINT rangesNum = desc->pParameters[i].DescriptorTable.NumDescriptorRanges;
        delete[rangesNum]  desc->pParameters[i].DescriptorTable.pDescriptorRanges; // ディスクリプタレンジ解放
    }
    delete[paramNum]   desc->pParameters; // ルートパラメータ解放

    UINT samplerNum = desc->NumStaticSamplers; // サンプラー数
    delete[samplerNum] desc->pStaticSamplers; // サンプラー解放
}




// 入力レイアウト作成
void Device::CreateInputLayout(InputLayout* inputLayout)
{
    auto& layout = inputLayout->_inputLayout;

    layout.resize(5);

    layout[0] =
    { // 頂点
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    layout[1] =
    { // 法線
        "NORMAL",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    layout[2] =
    { // uv
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    layout[3] =
    { // オブジェクトインデックス
        "OBJECT_INDEX",
        0,
        DXGI_FORMAT_R8_UINT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    layout[4] =
    { // テクスチャインデックス
        "TEXTURE_INDEX",
        0,
        DXGI_FORMAT_R8_UINT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
}




// パイプラインステート作成
HRESULT Device::CreatePipeline(
    Pipeline* pipeline,
    RootSignature* rootSignature,
    InputLayout* inputLayout,
    VShader* vShader,
    PShader* pShader)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc =
        GetPipelineStateDesc(
            rootSignature->_rootSignature.Get(),
            inputLayout->_inputLayout,
            vShader->_vShader.Get(),
            pShader->_pShader.Get());

    return _device->CreateGraphicsPipelineState(
        &desc,
        IID_PPV_ARGS(pipeline->_pipelineState.ReleaseAndGetAddressOf()));
}

// パイプラインステートディスクリプタ
D3D12_GRAPHICS_PIPELINE_STATE_DESC Device::GetPipelineStateDesc(
    ID3D12RootSignature* rootSignature,
    std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout,
    ID3DBlob* vShader,
    ID3DBlob* pShader)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};

    desc.pRootSignature =
        rootSignature;
    desc.InputLayout =
        GetInputLayoutDesc(inputLayout);
    desc.VS =
        GetVertexShaderDesc(vShader);
    desc.PS =
        GetPixelShaderDesc(pShader);
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
    desc.SampleDesc.Count = 1;

    desc.DepthStencilState =
        GetDepthStencilDesc();
    desc.DSVFormat = // 32ビットfloat値を深度値に使用
        DXGI_FORMAT_D32_FLOAT;

    return desc;
}

// インプットレイアウトディスクリプタ
D3D12_INPUT_LAYOUT_DESC Device::GetInputLayoutDesc(
    std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout)
{
    D3D12_INPUT_LAYOUT_DESC desc = {};

    desc.pInputElementDescs =
        inputLayout.data();
    desc.NumElements =
        static_cast<UINT>(inputLayout.size());

    return desc;
}

// 頂点シェーダディスクリプタ
D3D12_SHADER_BYTECODE Device::GetVertexShaderDesc(
    ID3DBlob* vertShaderBlob)
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        vertShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        vertShaderBlob->GetBufferSize();

    return desc;
}

// ピクセルシェーダディスクリプタ
D3D12_SHADER_BYTECODE Device::GetPixelShaderDesc(
    ID3DBlob* pixelShaderBlob)
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        pixelShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        pixelShaderBlob->GetBufferSize();

    return desc;
}

// ブレンドステートディスクリプタ
D3D12_BLEND_DESC Device::GetBlendStateDesc()
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

// レンダーターゲットステートディスクリプタ
D3D12_RENDER_TARGET_BLEND_DESC Device::GetRenderTargetBlendDesc()
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

// ラスタライザディスクリプタ
D3D12_RASTERIZER_DESC Device::GetRasterizerDesc()
{
    D3D12_RASTERIZER_DESC desc = {};

    desc.MultisampleEnable =
        false;
    desc.CullMode = // カリング　裏側は塗らない
        D3D12_CULL_MODE_BACK;
    desc.FillMode =
        D3D12_FILL_MODE_SOLID;
    desc.DepthClipEnable =
        true;

    return desc;
}

// デプスステンシルディスクリプタ
D3D12_DEPTH_STENCIL_DESC Device::GetDepthStencilDesc()
{
    D3D12_DEPTH_STENCIL_DESC desc = {};

    desc.DepthEnable = // デプスステンシルバッファを利用
        true;
    desc.DepthWriteMask = // ピクセル描画時に深度値を書き込む
        D3D12_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = // 深度値が小さいほうを採用
        D3D12_COMPARISON_FUNC_LESS;

    return desc;
}




// Direct3D11系作成
HRESULT Device::CreateD3D11(
    Device11* device11,
    DeviceContext* deviceContext,
    CmdQueue* cmdQueue)
{
    ComPtr<ID3D11On12Device> device11Com;
    ComPtr<ID3D11DeviceContext> deviceContextCom;

    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    flags += D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT result;

    ComPtr<ID3D11Device> device11Origin;

    result =  D3D11On12CreateDevice(
        _device.Get(),
        flags,
        nullptr, // 3D12の機能レベル使用
        0,       // 機能レベル配列サイズ(nullptrのため0）
        reinterpret_cast<IUnknown**>(cmdQueue->GetCmdQueuePtr()),
        1, // キューの個数 1
        0, // ノードマスク
        device11Origin.ReleaseAndGetAddressOf(),
        deviceContextCom.ReleaseAndGetAddressOf(),
        nullptr); // 機能レベル返却先 nullptr
    if(FAILED(result)) return result;

    result = device11Origin.As(&device11Com);
    if(FAILED(result)) return result;

    device11->     SetDevice11(device11Com);
    deviceContext->SetDeviceContext(deviceContextCom);
    return result;
}




// Direct3Dデバイスセット
void Device::SetDevice(ComPtr<ID3D12Device> device){_device = device;}

Device::Device(){}
Device::~Device(){}