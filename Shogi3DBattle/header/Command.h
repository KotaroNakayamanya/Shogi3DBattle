#pragma once

#include<d3d12.h>
#include<wrl.h>

class Command
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12CommandAllocator>    _commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> _commandList;
    ComPtr<ID3D12CommandQueue>        _commandQueue;

    HRESULT CreateCommandAllocator();
    HRESULT CreateCommandList();
    HRESULT CreateCommandQueue();


public:
    HRESULT CreateCommandObject();
};