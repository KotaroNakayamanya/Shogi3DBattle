#pragma once

#include<d3d12.h>
#include<wrl.h>

class CmdQueue
{
    friend class Device; // Direct3Dから参照可能
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandQueue> _cmdQueue; // コマンドキュー

public:
    ID3D12CommandQueue* GetCmdQueue(); // コマンドキューを返す

    CmdQueue();
    ~CmdQueue();
};