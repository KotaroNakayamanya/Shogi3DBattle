#include"Device.h"
#include<d3dcompiler.h>
#include<cassert>
#include<memory>

#pragma comment(lib, "d3dcompiler.lib")

// コマンドアロケータオブジェクト作成
HRESULT Device::CreateComAllocator(ComAllocator* comAllocator)
{
    return _device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(comAllocator->_comAllocator.ReleaseAndGetAddressOf()));
}




// コマンドリスト作成
HRESULT Device::CreateComList(ComList* comList, ComAllocator* comAllocator)
{
    return _device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        comAllocator->_comAllocator.Get(),
        nullptr,
        IID_PPV_ARGS(comList->_comList.ReleaseAndGetAddressOf()));
}




// コマンドキュー作成
HRESULT Device::CreateComQueue(ComQueue* comQueue)
{
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc = GetComQueueDesc();

    return _device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(comQueue->_comQueue.ReleaseAndGetAddressOf()));
}

// コマンドキューディスクリプタ
D3D12_COMMAND_QUEUE_DESC Device::GetComQueueDesc()
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




// RTVヒープ作成
HRESULT Device::CreateRTVHeap(RTVHeap* rtvHeap, SwapChain* swapChain)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetRTVHeapDesc(swapChain->GetRTBuffNum());

    return _device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(rtvHeap->_rtvHeap.ReleaseAndGetAddressOf()));
}

// RTVヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC Device::GetRTVHeapDesc(UINT rtBuffNum)
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = // タイプ RTV
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask =
        0;
    desc.NumDescriptors = // レンダーターゲットバッファ数
        rtBuffNum;
    desc.Flags =
        D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return desc;
}




// RTV作成
HRESULT Device::CreateRTV(RTV* rtv, RTVHeap* rtvHeap, SwapChain* swapChain, UINT i)
{
    HRESULT result;

    result =  swapChain->GetSwapChain()->GetBuffer(
        i, 
        IID_PPV_ARGS(rtv->_rtv.ReleaseAndGetAddressOf()));
    if(FAILED(result)) return result;

    // RTVヒープの中のどこのアドレスに入れるか計算する
    auto rtvHandle = rtvHeap->_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    auto rtvOffset = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    rtvHandle.ptr += rtvOffset * i;

    _device->CreateRenderTargetView(
        rtv->_rtv.Get(),
        nullptr,
        rtvHandle);

    rtv->_rtvHandle = rtvHandle;

    return S_OK;
}




// デプスステンシルバッファ作成
HRESULT Device::CreateDSBuff(DSBuff* dsBuff, GameWindow* gameWindow)
{
    D3D12_HEAP_PROPERTIES heapProp =
        GetDSHeapProp();
    D3D12_RESOURCE_DESC resourceDesc =
        GetDSResourceDesc(gameWindow->GetWindowWidth(), gameWindow->GetWindowHeight());
    D3D12_CLEAR_VALUE clearValue =
        GetClearValue();
 
    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE, 
        &clearValue,
        IID_PPV_ARGS(dsBuff->_dsBuff.ReleaseAndGetAddressOf()));
}

// デプスステンシルヒーププロパティ
D3D12_HEAP_PROPERTIES Device::GetDSHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_DEFAULT;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

// デプスステンシルリソースディスクリプタ
D3D12_RESOURCE_DESC Device::GetDSResourceDesc(
    UINT windowWidth, UINT windowHeight)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    desc.Width =
        windowWidth;
    desc.Height =
        windowHeight;
    desc.DepthOrArraySize =
        1;
    desc.Format = // 深度値書き込み用
        DXGI_FORMAT_D32_FLOAT;  
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_UNKNOWN;
    desc.Flags = // デプスステンシルとして使用
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    desc.SampleDesc =
        GetSampleDesc();

    return desc;
}

// クリアバリュー
D3D12_CLEAR_VALUE Device::GetClearValue()
{
    D3D12_CLEAR_VALUE clearValue = {};

    clearValue.DepthStencil.Depth = // 深さの初期値を最大値に
        1.0f;
    clearValue.Format = // float値
        DXGI_FORMAT_D32_FLOAT;

    return clearValue;
}




// デプスステンシルヒープ作成
HRESULT Device::CreateDSVHeap(DSVHeap* dsvHeap)
{
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = GetDSVHeapDesc();

    return _device->CreateDescriptorHeap(
        &dsvHeapDesc,
        IID_PPV_ARGS(dsvHeap->_dsvHeap.ReleaseAndGetAddressOf()));
}

// DSVヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC Device::GetDSVHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};

    desc.NumDescriptors =
        1;
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

    return desc;
}




// DSV作成
void Device::CreateDSV(DSV* dsv, DSVHeap* dsvHeap, DSBuff* dsBuff)
{
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc =  GetDSVDesc();

    auto dsvHandle = dsvHeap->_dsvHeap->GetCPUDescriptorHandleForHeapStart();

    _device->CreateDepthStencilView(
        dsBuff->_dsBuff.Get(),
        &dsvDesc,
        dsvHandle);

    dsv->_dsvHandle = dsvHandle;
}


// DSVディスクリプタ
D3D12_DEPTH_STENCIL_VIEW_DESC Device::GetDSVDesc()
{
    D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};

    desc.Format = // float値
        DXGI_FORMAT_D32_FLOAT;
    desc.ViewDimension = // 2Dテクスチャ
        D3D12_DSV_DIMENSION_TEXTURE2D;
    desc.Flags =
        D3D12_DSV_FLAG_NONE;

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




template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 頂点シェーダバイナリ作成
HRESULT Device::CreateVShader(VShader* vShader)
{
    ComPtr<ID3DBlob> errBlob;

    return D3DCompileFromFile(
        L"shader/VertexShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VShader",
        "vs_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        vShader->_vShaderBlob.ReleaseAndGetAddressOf(),
        errBlob              .ReleaseAndGetAddressOf());
}

// ピクセルシェーダバイナリ作成
HRESULT Device::CreatePShader(PShader* pShader)
{
    ComPtr<ID3DBlob> errBlob;

    return D3DCompileFromFile(
        L"shader/PixelShader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PShader",
        "ps_5_1",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        pShader->_pShaderBlob.ReleaseAndGetAddressOf(),
        errBlob              .ReleaseAndGetAddressOf());
}




// 頂点バッファ作成
HRESULT Device::CreateVertBuff(VertBuff* vertBuff, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetVertHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetVertResourceDesc(byteSize);

    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(vertBuff->_vertBuff.ReleaseAndGetAddressOf()));
}

// インデックスバッファ作成
HRESULT Device::CreateIdxBuff(IdxBuff* idxBuff, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetVertHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetVertResourceDesc(byteSize);

    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(idxBuff->_idxBuff.ReleaseAndGetAddressOf()));

}

// 頂点ヒーププロパティ
D3D12_HEAP_PROPERTIES Device::GetVertHeapProp()
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

// 頂点リソースディスクリプタ
D3D12_RESOURCE_DESC Device::GetVertResourceDesc(UINT byteSize)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Width =
        byteSize;
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




// テクスチャバッファオブジェクト作成
HRESULT Device::CreateTexBuff(TexBuff* texBuff)
{
    D3D12_HEAP_PROPERTIES heapProp = GetTexHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetTexResourceDesc();
 
    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, // テクスチャ
        nullptr,
        IID_PPV_ARGS(texBuff->_texBuff.ReleaseAndGetAddressOf()));
}

// テクスチャヒーププロパティ
D3D12_HEAP_PROPERTIES Device::GetTexHeapProp()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_CUSTOM;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    prop.MemoryPoolPreference = // 転送L0
        D3D12_MEMORY_POOL_L0;
    prop.CreationNodeMask =
        0;
    prop.VisibleNodeMask =
        0;

    return prop;
}

// テクスチャリソースディスクリプタ
D3D12_RESOURCE_DESC Device::GetTexResourceDesc()
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    desc.Height =
        256;
    desc.Width =
        256;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;  
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_UNKNOWN;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.SampleDesc =
        GetSampleDesc();

    return desc;
}

// サンプリングディスクリプタ
DXGI_SAMPLE_DESC Device::GetSampleDesc()
{
    DXGI_SAMPLE_DESC desc = {};

    desc.Count   = 1; // サンプリング数
    desc.Quality = 0; // クオリティ（0は最低）

    return desc;
}




// コンスタントオブジェクト作成
HRESULT Device::CreateConstBuff(ConstBuff* constBuff, UINT verticesByteSize)
{
    D3D12_HEAP_PROPERTIES heapProp =
        GetConstHeapProp();
    D3D12_RESOURCE_DESC resourceDesc =
        GetConstResourceDesc(verticesByteSize);

    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(constBuff->_constBuff.ReleaseAndGetAddressOf()));
}

// ヒーププロパティ
D3D12_HEAP_PROPERTIES Device::GetConstHeapProp()
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

// リソースディスクリプタ
D3D12_RESOURCE_DESC Device::GetConstResourceDesc(UINT verticesByte)
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Height =
        1;
    desc.Width =
        (verticesByte + 0xff) & ~0xff;
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




// CSUヒープ作成
HRESULT Device::CreateCSUHeap(CSUHeap* csuHeap)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetCSUHeapDesc();

    return _device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(csuHeap->_csuHeap.ReleaseAndGetAddressOf()));    

    return S_OK;
}

// CSUヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC Device::GetCSUHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};

    desc.Type = // SRV, CBV用
        D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        2;
    desc.Flags = // シェーダから使用可能
        D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    return desc;
}

// CBV作成
void Device::CreateCBV(CBV* cbv, CSUHeap* csuHeap, ConstBuff* constBuff)
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = GetCBVDesc(constBuff->_constBuff.Get());

    auto cbvHandle = csuHeap->_csuHeap->GetCPUDescriptorHandleForHeapStart();

    _device->CreateConstantBufferView(
        &cbvDesc,
        cbvHandle);

    // GPUハンドル取得
    cbv->_cbvHandle = csuHeap->_csuHeap->GetGPUDescriptorHandleForHeapStart();
}

// CBVディスクリプタ
D3D12_CONSTANT_BUFFER_VIEW_DESC Device::GetCBVDesc(ID3D12Resource* constBuff) 
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC desc = {};

    desc.BufferLocation = constBuff->GetGPUVirtualAddress();
    desc.SizeInBytes = constBuff->GetDesc().Width * constBuff->GetDesc().Height;

    return desc;
}

// SRV作成
void Device::CreateSRV(SRV* srv, CSUHeap* csuHeap, TexBuff* texBuff)
{
    
    auto srvHandle = csuHeap->_csuHeap->GetCPUDescriptorHandleForHeapStart();
    auto offset    = _device->GetDescriptorHandleIncrementSize(
                    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    srvHandle.ptr += offset;

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = GetSRVDesc();

    _device->CreateShaderResourceView(
        texBuff->_texBuff.Get(),
        &srvDesc,
        srvHandle);

    // GPUハンドル取得
    srv->_srvHandle = csuHeap->_csuHeap->GetGPUDescriptorHandleForHeapStart();
    srv->_srvHandle.ptr +=  offset;
}

// SRVディスクリプタ
D3D12_SHADER_RESOURCE_VIEW_DESC Device::GetSRVDesc()
{
    D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Shader4ComponentMapping =
        D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    desc.ViewDimension =
        D3D12_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels =
        1;

    return desc;
}




// ルートシグネチャ作成
HRESULT Device::CreateRootSignature(RootSignature* rootSignature)
{  
    ComPtr<ID3DBlob> _rootSignatureBlob = GetRootSignatureBlob(); // ルートシグネチャバイナリ作成

    return _device->CreateRootSignature(
        0,
        _rootSignatureBlob->GetBufferPointer(),
        _rootSignatureBlob->GetBufferSize(),
        IID_PPV_ARGS(rootSignature->_rootSignature.ReleaseAndGetAddressOf()));
}

// ルートシグネチャBlob取得
ComPtr<ID3DBlob> Device::GetRootSignatureBlob()
{
    ComPtr<ID3DBlob> rootSignatureBlob;
    ComPtr<ID3DBlob> errorBlob;

    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc =
        GetRootSignatureDesc();

    D3D12SerializeRootSignature(
        &rootSignatureDesc,
        D3D_ROOT_SIGNATURE_VERSION_1_0,
        rootSignatureBlob.ReleaseAndGetAddressOf(),
        errorBlob.        ReleaseAndGetAddressOf());

    DeleteRootSignatureDescMemory(&rootSignatureDesc); // ディスクリプタで使用されたメモリ開放

    return rootSignatureBlob;
}

// ルートシグネチャディスクリプタ
D3D12_ROOT_SIGNATURE_DESC Device::GetRootSignatureDesc()
{
    D3D12_ROOT_SIGNATURE_DESC desc = {};

    UINT paramNum = 2;
    UINT samplerNum = 1;

    std::vector<D3D12_ROOT_PARAMETER>* rootParameterPtr =
        new std::vector<D3D12_ROOT_PARAMETER>;
    *rootParameterPtr = GetRootParams(paramNum);

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
        1;

    return desc;
}

// ルートパラメータ
std::vector<D3D12_ROOT_PARAMETER> Device::GetRootParams(UINT paramNum)
{
    std::vector<D3D12_ROOT_PARAMETER> descs = {};
    descs.resize(paramNum);
 
    // CBV
    descs[0].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[0].ShaderVisibility = // 頂点シェーダで利用可能
        D3D12_SHADER_VISIBILITY_VERTEX;
    descs[0].DescriptorTable =
        GetDescTable(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1);

    // SRV
    descs[1].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[1].ShaderVisibility = // ピクセルシェーダで利用可能
        D3D12_SHADER_VISIBILITY_PIXEL;
    descs[1].DescriptorTable =
        GetDescTable(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1);

    return descs;
}

// ディスクリプタテーブル
D3D12_ROOT_DESCRIPTOR_TABLE Device::GetDescTable(
    D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
    UINT rangeNum)
{
    D3D12_ROOT_DESCRIPTOR_TABLE desc = {};

    std::vector<D3D12_DESCRIPTOR_RANGE>* descRangePtr =
        new std::vector<D3D12_DESCRIPTOR_RANGE>;

    // 派生クラスのオーバーライドが呼ばれる
    *descRangePtr = GetDescRanges(rangeType, rangeNum);

    desc.pDescriptorRanges =
        descRangePtr->data();
    desc.NumDescriptorRanges =
        rangeNum;

    return desc;
}

// ディスクリプタレンジ
std::vector<D3D12_DESCRIPTOR_RANGE> Device::GetDescRanges(
    D3D12_DESCRIPTOR_RANGE_TYPE rangeType,
    UINT rangeNum)
{
    std::vector<D3D12_DESCRIPTOR_RANGE> descs = {};
    descs.resize(rangeNum);

    UINT slotNo = 0;
    for (auto& desc : descs)
    {
        desc.NumDescriptors = // ディスクリプタ数
            1;
        desc.RangeType = // タイプ
            rangeType;
        desc.BaseShaderRegister = // スロット0から
            slotNo;
        desc.OffsetInDescriptorsFromTableStart =
            D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

        slotNo++;
    }
    

    return descs;
}

// サンプラーディスクリプタ
std::vector<D3D12_STATIC_SAMPLER_DESC> Device::GetSamplerDescs(UINT samplerNum)
{
    std::vector<D3D12_STATIC_SAMPLER_DESC> descs = {};
    descs.resize(samplerNum);


    descs[0].AddressU = // 横
        D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    descs[0].AddressV = // 縦
        D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    descs[0].AddressW = // 奥行き
        D3D12_TEXTURE_ADDRESS_MODE_WRAP;
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
    UINT paramNum   = desc->NumParameters;     // ルートパラメータ数
    for (int i = 0; i < paramNum; i++) // ルートパラメータごとのディスクリプタレンジを解放する
    {
        UINT rangesNum  = desc->pParameters[i].DescriptorTable.NumDescriptorRanges;
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

    layout.resize(3);

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
            vShader->_vShaderBlob.Get(),
            pShader->_pShaderBlob.Get());

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
    desc.SampleDesc =
        GetSampleDesc();
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
        inputLayout.size();
 
    return desc;
}

// 頂点シェーダディスクリプタ
D3D12_SHADER_BYTECODE Device::GetVertexShaderDesc(
    ID3DBlob* vertexShaderBlob)
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        vertexShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        vertexShaderBlob->GetBufferSize();

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




// Direct3Dデバイスを渡す
ID3D12Device* Device::GetDevice()
{
    return _device.Get();
}

Device::Device(){}
Device::~Device(){}