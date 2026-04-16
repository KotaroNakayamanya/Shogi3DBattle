#include"Device.h"
#include<cassert>
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

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// コマンドアロケータオブジェクト作成
ComPtr<ID3D12CommandAllocator> Device::CreateCmdAllocator()
{
    ComPtr<ID3D12CommandAllocator> comPtr;

    HRESULT result;
    result = _device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));
    assert(SUCCEEDED(result));

    return comPtr;
}

// コマンドリスト作成
ComPtr<ID3D12GraphicsCommandList> Device::CreateCmdList(ID3D12CommandAllocator* cmdAllocator)
{
    ComPtr<ID3D12GraphicsCommandList> comPtr;

    HRESULT result;
    result = _device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        cmdAllocator,
        nullptr,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));
    assert(SUCCEEDED(result));

    return comPtr;
}

// コマンドキュー作成
ComPtr<ID3D12CommandQueue> Device::CreateCmdQueue()
{
    ComPtr<ID3D12CommandQueue> comPtr;
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = GetCmdQueueDesc();

    HRESULT result;
    result = _device->CreateCommandQueue(
        &cmdQueueDesc,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));
    assert(SUCCEEDED(result));

    return comPtr;
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
ComPtr<ID3D12Fence> Device::CreateFence(unsigned int fenceVal)
{
    ComPtr<ID3D12Fence> comPtr;

    HRESULT result;
    result = _device->CreateFence(
        fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(comPtr.ReleaseAndGetAddressOf()));
    assert(SUCCEEDED(result));

    return comPtr;
}




// バッファ作成
ComPtr<ID3D12Resource> Device::CreateBuff(UINT width, UINT height, BuffType buffType)
{
    switch (buffType)
    {
    case BuffType::DEPTH_STENCIL:
        _buffFactory.reset(new DSBuffFactory());
        break;

    case BuffType::VERTEX:
        _buffFactory.reset(new VertBuffFactory());
        break;

    case BuffType::INDEX:
        _buffFactory.reset(new IdxBuffFactory());
        break;

    case BuffType::CONSTANT:
        _buffFactory.reset(new ConstBuffFactory());
         break;

    case BuffType::TEXTURE:
        _buffFactory.reset(new TexBuffFactory());
        break;

    case BuffType::RENDER_TEX:
        _buffFactory.reset(new RenderTexBuffFactory());
        break;

    default:
        return nullptr;
    }

    return _buffFactory->CreateBuff(width, height, _device.Get());
}

// ヒープ作成
HRESULT Device::CreateHeap(Heap* heap, UINT descNum, HeapType heapType)
{
    switch (heapType)
    {
    case HeapType::RTV:
        _heapFactory.reset(new RTVHeapFactory());
        break;

    case HeapType::DSV:
        _heapFactory.reset(new DSVHeapFactory());
        break;

    case HeapType::CSU:
        _heapFactory.reset(new CSUHeapFactory());
        break;

    default:
        return E_FAIL;
    }

    return _heapFactory->CreateHeap(heap, descNum, _device.Get());
}

// ヒープ作成（CSU）
HRESULT Device::CreateCSUHeap(CSUHeap* csuHeap, UINT cbvNum, UINT srvNum, UINT uavNum, HeapType heapType)
{
    // CSUヒープ内訳取得
    csuHeap->SetCBVNum(cbvNum);
    csuHeap->SetSRVNum(srvNum);
    csuHeap->SetUAVNum(uavNum);

    return CreateHeap(csuHeap, cbvNum + srvNum + uavNum, heapType);
}

// ビュー作成
void Device::CreateView(Heap* heap, UINT i, ID3D12Resource* buff, View::ViewType viewType)
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
void Device::CreateCSUView(CSUHeap* csuHeap, UINT i, ID3D12Resource* buff, View::ViewType viewType)
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



// パイプラインステート作成
HRESULT Device::CreatePipeline(
    Pipeline* pipeline,
    RootSignature* rootSignature,
    ID3DBlob* vShader,
    ID3DBlob* pShader)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc =
        GetPipelineStateDesc(
            rootSignature->_rootSignature.Get(),
            vShader,
            pShader);

    auto inputLayout = CreateInputLayout();
    desc.InputLayout = GetInputLayoutDesc(inputLayout);
    
    return _device->CreateGraphicsPipelineState(
        &desc,
        IID_PPV_ARGS(pipeline->_pipelineState.ReleaseAndGetAddressOf()));
}

// パイプラインステートディスクリプタ
D3D12_GRAPHICS_PIPELINE_STATE_DESC Device::GetPipelineStateDesc(
    ID3D12RootSignature* rootSignature,
    ID3DBlob* vShader,
    ID3DBlob* pShader)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};

    desc.pRootSignature =
        rootSignature;
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

// 頂点レイアウト作成
std::vector<D3D12_INPUT_ELEMENT_DESC> Device::CreateInputLayout()
{
    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;

    inputLayout.resize(6);

    inputLayout[0] =
    { // 頂点
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[1] =
    { // 法線
        "NORMAL",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[2] =
    { // uv
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[3] =
    { // オブジェクトインデックス
        "OBJECT_INDEX",
        0,
        DXGI_FORMAT_R8_UINT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[4] =
    { // 基本テクスチャインデックス
        "BASIC_TEXTURE_INDEX",
        0,
        DXGI_FORMAT_R8_UINT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[5] =
    { // デザインテクスチャインデックス
        "DESIGN_TEXTURE_INDEX",
        0,
        DXGI_FORMAT_R8_UINT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };

    return inputLayout;
}

// インプットレイアウトディスクリプタ
D3D12_INPUT_LAYOUT_DESC Device::GetInputLayoutDesc(std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout)
{
    
    D3D12_INPUT_LAYOUT_DESC desc = {};

    desc.pInputElementDescs =
        inputLayout.data();
    desc.NumElements =
        static_cast<unsigned int>(inputLayout.size());

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




// DirectX12デバイスセット
void Device::SetDevice(ComPtr<ID3D12Device> device){_device = device;}
ID3D12Device* Device::GetDevice(){return _device.Get();} // DirectX12デバイスを返す

Device::Device(ComPtr<ID3D12Device> comPtr) : _device(comPtr){}