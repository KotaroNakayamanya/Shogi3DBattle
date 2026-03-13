#pragma once

#include<d3d12.h>
#include<wrl.h>

class RootSignature
{
    friend class Device; // Direct3Dから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12RootSignature> _rootSignature; // ルートシグネチャ

public:
    ID3D12RootSignature* GetRootSignature(); // ルートシグネチャを渡す

    RootSignature();
    ~RootSignature();
};