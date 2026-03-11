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

    void SetRenderTarget( // レンダーターゲットセット
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
        D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle); // レンダーターゲットクリア
    void ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle); // デプスステンシルクリア

    void SetResourceBarrier(D3D12_RESOURCE_BARRIER resourceBarrier); // リソースバリアセット

    ID3D12GraphicsCommandList* GetCommandList(); // コマンドリストを返す

    CommandList();
    ~CommandList();
};