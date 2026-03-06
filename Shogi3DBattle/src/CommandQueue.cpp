#include"CommandQueue.h"

// コマンドキュー作成
HRESULT CommandQueue::CreateCommandQueue(ID3D12Device* device)
{
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc = GetCommandQueueDesc();

    return device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(_commandQueue.ReleaseAndGetAddressOf()));
}

// コマンドキューディスクリプタ
D3D12_COMMAND_QUEUE_DESC CommandQueue::GetCommandQueueDesc()
{
    D3D12_COMMAND_QUEUE_DESC desc = {};

    desc.Type =    // コマンドリストタイプの種類
        D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = // アプリケーション優先度 通常
        D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = // タイムアウトなし
        D3D12_COMMAND_QUEUE_FLAG_NONE; 
    desc.NodeMask =
        0;

    return desc;
}

// コマンドキューを返す
ID3D12CommandQueue* CommandQueue::GetCommandQueue()
{
    return _commandQueue.Get();
}

CommandQueue::CommandQueue(){}
CommandQueue::~CommandQueue(){}