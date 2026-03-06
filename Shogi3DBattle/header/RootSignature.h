#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

class RootSignature
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12RootSignature> _rootSignature; // ルートシグネチャ

    ComPtr<ID3DBlob> GetRootSignatureBlob(); // ルートシグネチャBlob取得


    // ディスクリプタレンジ作成用ステート
    class RangeTypeState
    {
    private:
        UINT rangeNum; // レンジ数
    public:
        // 仮想関数
        virtual std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges() = 0;

        UINT GetRangeNum(){return rangeNum;}

        RangeTypeState(UINT num):rangeNum(num){}
        RangeTypeState()        :rangeNum(-1){}
        ~RangeTypeState(){}
    };

    // CBVディスクリプタレンジ作成
    class RangeTypeCBV : public RangeTypeState
    {
    private:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetCBVDescRanges(); // CBVディスクリプタレンジ
    public:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges() override
        {
            return GetCBVDescRanges();
        }

        RangeTypeCBV(UINT num):RangeTypeState(num){}
        RangeTypeCBV():        RangeTypeState(-1){}
        ~RangeTypeCBV(){}
    };

    // SRVディスクリプタレンジ作成
    class RangeTypeSRV : public RangeTypeState
    {
    private:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetSRVDescRanges(); // SRVディスクリプタレンジ
    public:
        std::vector<D3D12_DESCRIPTOR_RANGE> GetDescRanges() override
        {
            return GetSRVDescRanges();
        }

        RangeTypeSRV(UINT num):RangeTypeState(num){}
        RangeTypeSRV():        RangeTypeState(-1){}
        ~RangeTypeSRV(){}
    };

    D3D12_ROOT_SIGNATURE_DESC GetRootSignatureDesc(); // ルートシグネチャディスクリプタ
    std::vector<D3D12_ROOT_PARAMETER> GetRootParams(UINT paramNum); // ルートパラメータ
    D3D12_ROOT_DESCRIPTOR_TABLE GetDescTable(RangeTypeState* rangeType); // ディスクリプタテーブル
    std::vector<D3D12_STATIC_SAMPLER_DESC> GetSamplerDescs(UINT samplerNum); // サンプラーディスクリプタ
 

    void DeleteRootSignatureDescMemory( // ディスクリプタで使用されたメモリ開放
        D3D12_ROOT_SIGNATURE_DESC* desc);


public:
    HRESULT CreateRootSignatureObj(ID3D12Device* device); // ルートシグネチャ作成  
    ID3D12RootSignature* GetRootSignature(); // ルートシグネチャを渡す

    RootSignature();
    ~RootSignature();
};