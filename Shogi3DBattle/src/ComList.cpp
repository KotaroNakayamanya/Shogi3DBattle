#include"ComList.h"

// レンダーターゲットセット
void ComList::SetRenderTarget(
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
    D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
    _comList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);
}

// デプスステンシルクリア
void ComList::ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
    _comList->ClearDepthStencilView(
        dsvHandle,
        D3D12_CLEAR_FLAG_DEPTH,
        1.0f, 0, 0, nullptr);
}

// レンダーターゲットクリア
void ComList::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle)
{
    float clearRTVColor[] =
        {0.0f, 0.3f, 0.0f, 1.0f};
    _comList->ClearRenderTargetView(
        rtvHandle, clearRTVColor, 0, nullptr);
}

// パイプラインセット
void ComList::SetPipeline(ID3D12PipelineState* pipelineState)
{
    _comList->SetPipelineState(pipelineState);
}

// ルートシグネチャセット
void ComList::SetRootSignature(ID3D12RootSignature* rootSignature)
{
    _comList->SetGraphicsRootSignature(rootSignature);
}

// リソースバリアセット
void ComList::SetResourceBarrier(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    _comList->ResourceBarrier(1, &resourceBarrier);
}

// CSUヒープセット
void ComList::SetCSUHeaps(ID3D12DescriptorHeap** csuHeaps)
{
    auto heapNum = sizeof(csuHeaps) / sizeof(ID3D12DescriptorHeap**);
    _comList->SetDescriptorHeaps(heapNum, csuHeaps);
}

// ディスクリプタテーブルセット
void ComList::SetDescriptorTable(UINT i, D3D12_GPU_DESCRIPTOR_HANDLE handle)
{
    _comList->SetGraphicsRootDescriptorTable(i, handle);
}

// ビューポートセット
void ComList::SetViewports(D3D12_VIEWPORT* viewports)
{
    auto viewportNum = sizeof(viewports) / sizeof(D3D12_VIEWPORT*);
    _comList->RSSetViewports(viewportNum, viewports);
}

// シザー矩形セット
void ComList::SetScissorRects(D3D12_RECT* scissorRects)
{
    auto scissorRectNum = sizeof(scissorRects) / sizeof(D3D12_RECT*);
    _comList->RSSetScissorRects(scissorRectNum, scissorRects);
}

// トポロジーセット
void ComList::SetTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
    _comList->IASetPrimitiveTopology(topology);
}

// 頂点バッファビューセット
void ComList::SetVertBuffViews(D3D12_VERTEX_BUFFER_VIEW* vertBuffViews)
{
    auto vertBuffViewNum = sizeof(vertBuffViews) / sizeof(D3D12_VERTEX_BUFFER_VIEW*);
    _comList->IASetVertexBuffers(0, vertBuffViewNum, vertBuffViews);
}

// インデックスバッファビューセット
void ComList::SetIdxBuffView(D3D12_INDEX_BUFFER_VIEW idxBuffView)
{
    _comList->IASetIndexBuffer(&idxBuffView);
}

// インデックス描画セット
void ComList::SetDrawWithIdx(Vertex* vertex)
{
    _comList->DrawIndexedInstanced(vertex->GetIndicesNum(), 1, 0, 0, 0);
}

// コマンドリストを返す
ID3D12GraphicsCommandList* ComList::GetComList(){return _comList.Get();}

ComList::ComList(){}
ComList::~ComList(){}