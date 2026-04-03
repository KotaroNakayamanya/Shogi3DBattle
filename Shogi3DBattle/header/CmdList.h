#pragma once

#include<d3d12.h>
#include<wrl.h>
#include"BufferedData.h"
#include"CmdAllocator.h"

class CmdList
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12GraphicsCommandList> _cmdList; // コマンドリスト

public:
    void SetResourceBarrier( // リソースバリアセット
        D3D12_RESOURCE_BARRIER resourceBarrier);
    void SetRenderTarget( // レンダーターゲットセット
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
        D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);
    void SetRenderTarget( // レンダーターゲットセット
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle);
    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle); // レンダーターゲットクリア
    void ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle); // デプスステンシルクリア

    void SetPipeline( // パイプラインセット
        ID3D12PipelineState* pipelineState);
    void SetRootSignature( // ルートシグネチャセット
        ID3D12RootSignature* rootSignature);
    void SetCSUHeaps( // CSUヒープセット
        UINT num, ID3D12DescriptorHeap** csuHeaps);
    void SetDescriptorTable( // ディスクリプタテーブルセット
        UINT i, D3D12_GPU_DESCRIPTOR_HANDLE handle);

    void SetViewports(UINT num, D3D12_VIEWPORT* viewports); // ビューポートセット
    void SetScissorRects(UINT num, D3D12_RECT* scissorRects); // シザー矩形セット

    void SetTopology(D3D_PRIMITIVE_TOPOLOGY topology); // トポロジーセット

    void SetVertBuffView(D3D12_VERTEX_BUFFER_VIEW vertBuffView); // 頂点バッファビューセット
    void SetIdxBuffView(D3D12_INDEX_BUFFER_VIEW idxBuffView);    // インデックスバッファビューセット

    void SetDrawWithIdx(BufferedData<unsigned short>* bufferedData); // インデックス描画セット

    void Close(); // コマンドクローズ

    void Reset(CmdAllocator* cmdAllocator); // コマンドリセット
    

    

    
    void SetCmdList(ComPtr<ID3D12GraphicsCommandList> cmdList); // コマンドリストセット
    ID3D12GraphicsCommandList* GetCmdList(); // コマンドリストを返す

    CmdList();
    ~CmdList();
};