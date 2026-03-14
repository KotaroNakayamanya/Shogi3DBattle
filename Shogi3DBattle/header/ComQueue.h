#pragma once

#include<d3d12.h>
#include<wrl.h>

class ComQueue
{
    friend class Device; // Direct3Dから参照可能
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandQueue> _comQueue; // コマンドキュー

    //D3D12_COMMAND_QUEUE_DESC GetComQueueDesc(); // コマンドキューディスクリプタ

public:
    //HRESULT CreateComQueue(ID3D12Device* device); // コマンドキュー作成
    ID3D12CommandQueue* GetComQueue(); // コマンドキューを返す

    ComQueue();
    ~ComQueue();
};