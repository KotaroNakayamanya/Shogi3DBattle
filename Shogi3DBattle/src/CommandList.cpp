#include"CommandList.h"

// コマンドリスト作成
HRESULT CommandList::CreateCommandList(
    ID3D12Device* device,
    ID3D12CommandAllocator* commandAllocator)
{
    return device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        commandAllocator,
        nullptr,
        IID_PPV_ARGS(_commandList.ReleaseAndGetAddressOf()));
}




// レンダーターゲットセット
void CommandList::SetRenderTarget(
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle,
    D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
    _commandList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);
}

// デプスステンシルクリア
void CommandList::ClearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
    _commandList->ClearDepthStencilView(
        dsvHandle,
        D3D12_CLEAR_FLAG_DEPTH,
        1.0f, 0, 0, nullptr);
}

// レンダーターゲットクリア
void CommandList::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle)
{
    float clearRTVColor[] =
        {0.0f, 0.3f, 0.0f, 1.0f};
    _commandList->ClearRenderTargetView(
        rtvHandle, clearRTVColor, 0, nullptr);
}

// パイプラインセット
void CommandList::SetPipeline(ID3D12PipelineState* pipelineState)
{
    _commandList->SetPipelineState(pipelineState);
}

// ルートシグネチャセット
void CommandList::SetRootSignature(ID3D12RootSignature* rootSignature)
{
    _commandList->SetGraphicsRootSignature(rootSignature);
}

// リソースバリアセット
void CommandList::SetResourceBarrier(D3D12_RESOURCE_BARRIER resourceBarrier)
{
    _commandList->ResourceBarrier(1, &resourceBarrier);
}

// CSUヒープセット
void CommandList::SetCSUHeaps(ID3D12DescriptorHeap** csuHeaps)
{
    auto heapsNum = sizeof(csuHeaps) / sizeof(ID3D12DescriptorHeap**);
    _commandList->SetDescriptorHeaps(heapsNum, csuHeaps);
}

// ディスクリプタテーブルセット
void CommandList::SetDescriptorTable(UINT i, D3D12_GPU_DESCRIPTOR_HANDLE handle)
{
    _commandList->SetGraphicsRootDescriptorTable(i, handle);
}

// コマンドリストを返す
ID3D12GraphicsCommandList* CommandList::GetCommandList()
{
    return _commandList.Get();
}

CommandList::CommandList(){}
CommandList::~CommandList(){}