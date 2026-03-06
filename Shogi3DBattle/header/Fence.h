#pragma once

#include<d3d12.h>
#include<wrl.h>

class Fence
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Fence> _fence; // フェンス
    UINT _fenceVal = 0; // フェンスの同期処理確認用

public:
    HRESULT CreateFence(ID3D12Device* device); // フェンス作成
    ID3D12Fence* GetFence(); // フェンスを返す
    UINT GetFenceVal(); // フェンス値を返す
    UINT GetIncrementFenceVal(); // フェンス値をインクリメントして返す

    Fence();
    ~Fence();
};