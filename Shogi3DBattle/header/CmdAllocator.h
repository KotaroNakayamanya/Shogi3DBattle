#pragma once

#include<d3d12.h>
#include<wrl.h>

class CmdAllocator
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandAllocator> _cmdAllocator; // コマンドアロケータ

public:
    void Reset(); // コマンドリセット

    void SetCmdAllocator(ComPtr<ID3D12CommandAllocator> cmdAllocator); // コマンドアロケータセット
    ID3D12CommandAllocator* GetCmdAllocator(); // コマンドアロケータを返す

    CmdAllocator();
    ~CmdAllocator();
};