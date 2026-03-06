#pragma once

#include<d3d12.h>
#include<wrl.h>

class CommandList
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12GraphicsCommandList> _commandList; // コマンドリスト

public:
    HRESULT CreateCommandList( // コマンドリスト作成
        ID3D12Device* device,
        ID3D12CommandAllocator* commandAllocator); 

    ID3D12GraphicsCommandList* GetCommandList(); // コマンドリストを返す

    CommandList();
    ~CommandList();
};