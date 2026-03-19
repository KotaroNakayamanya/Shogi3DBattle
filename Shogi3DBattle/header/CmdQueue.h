#pragma once

#include<d3d12.h>
#include<wrl.h>
#include"CmdList.h"

class CmdQueue
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandQueue> _cmdQueue; // コマンドキュー

public:
    void ExeCmd(CmdList* cmdList); // コマンド実行

    void SetCmdQueue(ComPtr<ID3D12CommandQueue> cmdQueue); // コマンドキューセット
    ID3D12CommandQueue* GetCmdQueue(); // コマンドキューを返す
    ID3D12CommandQueue** GetCmdQueuePtr(); // コマンドキューポインタを返す

    CmdQueue();
    ~CmdQueue();
};