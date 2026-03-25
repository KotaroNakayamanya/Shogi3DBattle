#include"CmdList.h"

// レンダーターゲットセット
void CmdList::SetRenderTarget(
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
    D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
    _cmdList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);
}

// レンダーターゲットセット
void CmdList::SetRenderTarget(
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle)
{
    _cmdList->OMSetRenderTargets(1, &rtvHandle, true, nullptr);
}

// デプスステンシルクリア
void CmdList::ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
    _cmdList->ClearDepthStencilView(
        dsvHandle,
        D3D12_CLEAR_FLAG_DEPTH,
        1.0f, 0, 0, nullptr);
}

// レンダーターゲットクリア
void CmdList::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle)
{
    float clearRTVColor[] =
        {1.0f, 1.0f, 1.0f, 1.0f};
    _cmdList->ClearRenderTargetView(
        rtvHandle, clearRTVColor, 0, nullptr);
}

// パイプラインセット
void CmdList::SetPipeline(ID3D12PipelineState* pipelineState)
{
    _cmdList->SetPipelineState(pipelineState);
}

// ルートシグネチャセット
void CmdList::SetRootSignature(ID3D12RootSignature* rootSignature)
{
    _cmdList->SetGraphicsRootSignature(rootSignature);
}

// リソースバリアセット
void CmdList::SetResourceBarrier(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    _cmdList->ResourceBarrier(1, &resourceBarrier);
}

// CSUヒープセット
void CmdList::SetCSUHeaps(UINT num, ID3D12DescriptorHeap** csuHeaps)
{
    _cmdList->SetDescriptorHeaps(num, csuHeaps);
}

// ディスクリプタテーブルセット
void CmdList::SetDescriptorTable(UINT i, D3D12_GPU_DESCRIPTOR_HANDLE handle)
{
    _cmdList->SetGraphicsRootDescriptorTable(i, handle);
}

// ビューポートセット
void CmdList::SetViewports(UINT num, D3D12_VIEWPORT* viewports)
{
    _cmdList->RSSetViewports(num, viewports);
}

// シザー矩形セット
void CmdList::SetScissorRects(UINT num, D3D12_RECT* scissorRects)
{
    auto aaa = scissorRects[0];
    auto bbb = scissorRects[1];
    _cmdList->RSSetScissorRects(num, scissorRects);
}

// トポロジーセット
void CmdList::SetTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
    _cmdList->IASetPrimitiveTopology(topology);
}

// 頂点バッファビューセット
void CmdList::SetVertBuffView(D3D12_VERTEX_BUFFER_VIEW vertBuffView)
{
    _cmdList->IASetVertexBuffers(0, 1, &vertBuffView);
}

// インデックスバッファビューセット
void CmdList::SetIdxBuffView(D3D12_INDEX_BUFFER_VIEW idxBuffView)
{
    _cmdList->IASetIndexBuffer(&idxBuffView);
}

// インデックス描画セット
void CmdList::SetDrawWithIdx(VertIndices* vertIndices)
{    
    auto aaa = vertIndices->GetVertIndicesSize();
    _cmdList->DrawIndexedInstanced(vertIndices->GetVertIndicesSize(), 1, 0, 0, 0);
}

// コマンドクローズ
void CmdList::Close()
{
    _cmdList->Close();
}

// コマンドリセット
void CmdList::Reset(CmdAllocator* cmdAllocator)
{
    _cmdList->Reset(cmdAllocator->GetCmdAllocator(), nullptr);
}




// コマンドリストセット
void CmdList::SetCmdList(ComPtr<ID3D12GraphicsCommandList> cmdList){_cmdList = cmdList;}
// コマンドリストを返す
ID3D12GraphicsCommandList* CmdList::GetCmdList(){return _cmdList.Get();}

CmdList::CmdList(){}
CmdList::~CmdList(){}