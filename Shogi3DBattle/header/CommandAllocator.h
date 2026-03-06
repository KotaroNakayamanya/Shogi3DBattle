#pragma once

#include<d3d12.h>
#include<wrl.h>

class CommandAllocator
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandAllocator> _commandAllocator; // コマンドアロケータ

public:
    HRESULT CreateCommandAllocator(ID3D12Device* device); // コマンドアロケータ作成
    ID3D12CommandAllocator* GetCommandAllocator();       // コマンドアロケータを返す

    CommandAllocator();
    ~CommandAllocator();
};