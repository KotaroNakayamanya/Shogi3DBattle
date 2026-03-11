#pragma once

#include<d3d12.h>
#include<wrl.h>

class CommandList
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12GraphicsCommandList> _commandList; // コマンドリスト

public:
    HRESULT CreateCommandList( // コマンドリスト作成
        ID3D12Device* device,
        ID3D12CommandAllocator* commandAllocator);

    void SetResourceBarrier( // リソースバリアセット
        D3D12_RESOURCE_BARRIER resourceBarrier);
    void SetRenderTarget( // レンダーターゲットセット
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
        D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);
    void SetPipeline( // パイプラインセット
        ID3D12PipelineState* pipelineState);
    void SetRootSignature( // ルートシグネチャセット
        ID3D12RootSignature* rootSignature);
    void SetCSUHeaps( // CSUヒープセット
        ID3D12DescriptorHeap** csuHeaps);
    void SetDescriptorTable( // ディスクリプタテーブルセット
        UINT i, D3D12_GPU_DESCRIPTOR_HANDLE handle);

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle); // レンダーターゲットクリア
    void ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle); // デプスステンシルクリア

    

    ID3D12GraphicsCommandList* GetCommandList(); // コマンドリストを返す

    CommandList();
    ~CommandList();
};