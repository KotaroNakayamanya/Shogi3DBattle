#include"Device.h"
#include<d3dcompiler.h>
#include<cassert>
#include<memory>

#pragma comment(lib, "d3dcompiler.lib")

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 頂点シェーダバイナリ作成
HRESULT Device::CreateVShader(VShader* vShaderObj)
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
        vShaderObj->_vShaderBlob.ReleaseAndGetAddressOf(),
        errBlob                 .ReleaseAndGetAddressOf());
}

// ピクセルシェーダバイナリ作成
HRESULT Device::CreatePShader(PShader* pShaderObj)
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
        pShaderObj->_pShaderBlob.ReleaseAndGetAddressOf(),
        errBlob                 .ReleaseAndGetAddressOf());
}




// 頂点バッファ作成
HRESULT Device::CreateVertBuff(VertBuff* vertBuffObj, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetVertHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetVertResourceDesc(byteSize);

    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(vertBuffObj->_vertBuff.ReleaseAndGetAddressOf()));
}

// インデックスバッファ作成
HRESULT Device::CreateIdxBuff(IdxBuff* idxBuffObj, UINT byteSize)
{
    D3D12_HEAP_PROPERTIES heapProp = GetVertHeapProp();
    D3D12_RESOURCE_DESC resourceDesc = GetVertResourceDesc(byteSize);

    return _device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(idxBuffObj->_idxBuff.ReleaseAndGetAddressOf()));

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
HRESULT Device::CreateConstBuff(ConstBuff* constBuffObj, UINT verticesByteSize)
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
        IID_PPV_ARGS(constBuffObj->_constBuff.ReleaseAndGetAddressOf()));
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




// ヒープ作成
HRESULT Device::CreateCSUHeap(CSUHeap* csuHeap)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetCSUHeapDesc();

    return _device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(csuHeap->_csuHeap.ReleaseAndGetAddressOf()));    

    return S_OK;
}

// ヒープディスクリプタ
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
    cbv->_cbvHandle = csuHeap->GetCSUHeap()->GetCPUDescriptorHandleForHeapStart();

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = GetCBVDesc(constBuff->_constBuff.Get());

    _device->CreateConstantBufferView(
        &cbvDesc,
        cbv->_cbvHandle);
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
    
    srv->_srvHandle = csuHeap->GetCSUHeap()->GetCPUDescriptorHandleForHeapStart();
    srv->_srvHandle.ptr += _device->GetDescriptorHandleIncrementSize(
                    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = GetSRVDesc();

    _device->CreateShaderResourceView(
        texBuff->_texBuff.Get(),
        &srvDesc,
        srv->_srvHandle);
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

    std::unique_ptr<RangeTypeState> state;
 
    // CBV
    state.reset(new RangeTypeCBV(1));
    descs[0].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[0].ShaderVisibility = // 頂点シェーダで利用可能
        D3D12_SHADER_VISIBILITY_VERTEX;
    descs[0].DescriptorTable =
        GetDescTable(state.get());

    // SRV
    state.reset(new RangeTypeSRV(1));
    descs[1].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[1].ShaderVisibility = // ピクセルシェーダで利用可能
        D3D12_SHADER_VISIBILITY_PIXEL;
    descs[1].DescriptorTable =
        GetDescTable(state.get());

    return descs;
}

// ディスクリプタテーブル
D3D12_ROOT_DESCRIPTOR_TABLE Device::GetDescTable(RangeTypeState* rangeType)
{
    D3D12_ROOT_DESCRIPTOR_TABLE desc = {};

    std::vector<D3D12_DESCRIPTOR_RANGE>* descRangePtr =
        new std::vector<D3D12_DESCRIPTOR_RANGE>;

    // 派生クラスのオーバーライドが呼ばれる
    *descRangePtr = rangeType->GetDescRanges();

    desc.pDescriptorRanges =
        descRangePtr->data();
    desc.NumDescriptorRanges =
        rangeType->GetRangeNum();;

    return desc;
}




// CBVディスクリプタレンジ
std::vector<D3D12_DESCRIPTOR_RANGE> Device::RangeTypeCBV::GetCBVDescRanges()
{
    std::vector<D3D12_DESCRIPTOR_RANGE> descs = {};
    descs.resize(GetRangeNum());

    UINT slotNo = 0;
    for (auto& desc : descs)
    {
        desc.NumDescriptors = // ディスクリプタ数
            1;
        desc.RangeType = // タイプ：CRV
            D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
        desc.BaseShaderRegister = // スロット0から
            slotNo;
        desc.OffsetInDescriptorsFromTableStart =
            D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

        slotNo++;
    }
    
    return descs;
}

// SRVディスクリプタレンジ
std::vector<D3D12_DESCRIPTOR_RANGE> Device::RangeTypeSRV::GetSRVDescRanges()
{
    std::vector<D3D12_DESCRIPTOR_RANGE> descs = {};
    descs.resize(GetRangeNum());

    UINT slotNo = 0;
    for (auto& desc : descs)
    {
        desc.NumDescriptors = // ディスクリプタ数
            1;
        desc.RangeType = // タイプ：SRV
            D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
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
    UINT rangesNum  = desc->pParameters->DescriptorTable.NumDescriptorRanges;
    UINT paramNum   = desc->NumParameters;
    UINT samplerNum = desc->NumStaticSamplers;

    delete[rangesNum]  desc->pParameters->DescriptorTable.pDescriptorRanges;
    delete[paramNum]   desc->pParameters;
    delete[samplerNum] desc->pStaticSamplers;
}




// Direct3Dデバイスを渡す
ID3D12Device* Device::GetDevice()
{
    return _device.Get();
}

Device::Device(){}
Device::~Device(){}