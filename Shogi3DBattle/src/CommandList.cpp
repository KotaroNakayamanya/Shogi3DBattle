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

// コマンドリストを返す
ID3D12GraphicsCommandList* CommandList::GetCommandList()
{
    return _commandList.Get();
}

CommandList::CommandList(){}
CommandList::~CommandList(){}