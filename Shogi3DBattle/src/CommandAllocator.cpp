#include"CommandAllocator.h"

// コマンドアロケータ作成
HRESULT CommandAllocator::CreateCommandAllocator(ID3D12Device* device)
{
    return device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(_commandAllocator.ReleaseAndGetAddressOf()));}

// コマンドアロケータを返す
ID3D12CommandAllocator* CommandAllocator::GetCommandAllocator()
{
    return _commandAllocator.Get();
}

CommandAllocator::CommandAllocator(){}
CommandAllocator::~CommandAllocator(){}