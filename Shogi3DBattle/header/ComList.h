#pragma once

#include<d3d12.h>
#include<wrl.h>
#include"Vertex.h"

class ComList
{
    friend class Device; // Direct3Dから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12GraphicsCommandList> _comList; // コマンドリスト

public:
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

    void SetViewports(D3D12_VIEWPORT* viewports); // ビューポートセット
    void SetScissorRects(D3D12_RECT* scissorRects); // シザー矩形セット

    void SetTopology(D3D_PRIMITIVE_TOPOLOGY topology); // トポロジーセット

    void SetVertBuffViews(D3D12_VERTEX_BUFFER_VIEW* vertBuffViews); // 頂点バッファビューセット
    void SetIdxBuffView(D3D12_INDEX_BUFFER_VIEW idxBuffViews);    // インデックスバッファビューセット

    void SetDrawWithIdx(Vertex* vertex); // インデックス描画セット

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle); // レンダーターゲットクリア
    void ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle); // デプスステンシルクリア

    

    ID3D12GraphicsCommandList* GetComList(); // コマンドリストを返す

    ComList();
    ~ComList();
};