#pragma once

#include<d3d12.h>
#include<wrl.h>
#include"CmdList.h"

class CmdQueue
{
    friend class Device; // Direct3Dから参照可能
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandQueue> _cmdQueue; // コマンドキュー

public:
    void ExeCmd(CmdList* cmdList); // コマンド実行

    ID3D12CommandQueue* GetCmdQueue(); // コマンドキューを返す

    CmdQueue();
    ~CmdQueue();
};