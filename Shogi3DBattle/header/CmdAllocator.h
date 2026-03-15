#pragma once

#include<d3d12.h>
#include<wrl.h>

class CmdAllocator
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandAllocator> _cmdAllocator; // コマンドアロケータ

public:
    ID3D12CommandAllocator* GetCmdAllocator();       // コマンドアロケータを返す

    CmdAllocator();
    ~CmdAllocator();
};