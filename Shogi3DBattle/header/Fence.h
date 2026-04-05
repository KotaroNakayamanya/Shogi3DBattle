#pragma once

#include<d3d12.h>
#include<wrl.h>

class Fence
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Fence> _fence; // フェンス
    unsigned int _fenceVal;     // フェンスの同期処理確認用

public:
    void         SetFence(ComPtr<ID3D12Fence> fence); // フェンスセット
    ID3D12Fence* GetFence();                          // フェンスを返す

    UINT64 GetFenceVal();                 // フェンス値を返す

    unsigned int GetIncrementFenceVal(); // フェンス値をインクリメントして返す
};