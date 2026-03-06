#include"RootSignature.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// ルートシグネチャ作成
HRESULT RootSignature::CreateRootSignatureObj(ID3D12Device* device)
{
    // バイナリ作成
    ComPtr<ID3DBlob> _rootSignatureBlob =
        GetRootSignatureBlob();

    return device->CreateRootSignature(
        0,
        _rootSignatureBlob->GetBufferPointer(),
        _rootSignatureBlob->GetBufferSize(),
        IID_PPV_ARGS(_rootSignature.ReleaseAndGetAddressOf()));
}

// ルートシグネチャBlob取得
ComPtr<ID3DBlob> RootSignature::GetRootSignatureBlob()
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

    // ディスクリプタで使用されたメモリ開放
    DeleteRootSignatureDescMemory(&rootSignatureDesc);

    return rootSignatureBlob;
}




// ルートシグネチャディスクリプタ
D3D12_ROOT_SIGNATURE_DESC RootSignature::GetRootSignatureDesc()
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
std::vector<D3D12_ROOT_PARAMETER> RootSignature::GetRootParams(UINT paramNum)
{
    std::vector<D3D12_ROOT_PARAMETER> descs = {};
    descs.resize(paramNum);
 
    // CBV
    descs[0].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[0].ShaderVisibility = // 頂点シェーダで利用可能
        D3D12_SHADER_VISIBILITY_VERTEX;
    descs[0].DescriptorTable =
        GetDescTable(new RangeTypeCBV(1));

    // SRV
    descs[1].ParameterType = // ディスクリプタテーブル
        D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    descs[1].ShaderVisibility = // ピクセルシェーダで利用可能
        D3D12_SHADER_VISIBILITY_PIXEL;
    descs[1].DescriptorTable =
        GetDescTable(new RangeTypeSRV(1));

    return descs;
}

// ディスクリプタテーブル
D3D12_ROOT_DESCRIPTOR_TABLE RootSignature::GetDescTable(RangeTypeState* rangeType)
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
std::vector<D3D12_DESCRIPTOR_RANGE> RootSignature::RangeTypeCBV::GetCBVDescRanges()
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
std::vector<D3D12_DESCRIPTOR_RANGE> RootSignature::RangeTypeSRV::GetSRVDescRanges()
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
std::vector<D3D12_STATIC_SAMPLER_DESC> RootSignature::GetSamplerDescs(UINT samplerNum)
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
void RootSignature::DeleteRootSignatureDescMemory(D3D12_ROOT_SIGNATURE_DESC* desc)
{
    UINT rangesNum  = desc->pParameters->DescriptorTable.NumDescriptorRanges;
    UINT paramNum   = desc->NumParameters;
    UINT samplerNum = desc->NumStaticSamplers;

    delete[rangesNum]  desc->pParameters->DescriptorTable.pDescriptorRanges;
    delete[paramNum]   desc->pParameters;
    delete[samplerNum] desc->pStaticSamplers;
}




// ルートシグネチャを渡す
ID3D12RootSignature* RootSignature::GetRootSignature()
{
    return _rootSignature.Get();
}


RootSignature::RootSignature(){}
RootSignature::~RootSignature(){}