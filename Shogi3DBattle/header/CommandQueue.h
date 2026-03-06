#pragma once

#include<d3d12.h>
#include<wrl.h>

class CommandQueue
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandQueue> _commandQueue; // コマンドキュー

    D3D12_COMMAND_QUEUE_DESC GetCommandQueueDesc(); // コマンドキューディスクリプタ

public:
    HRESULT CreateCommandQueue(ID3D12Device* device); // コマンドキュー作成
    ID3D12CommandQueue* GetCommandQueue(); // コマンドキューを返す

    CommandQueue();
    ~CommandQueue();
};