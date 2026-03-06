#include"Fence.h"

// フェンス作成
HRESULT Fence::CreateFence(ID3D12Device* device)
{
    return device->CreateFence(
        _fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
}

// フェンスを返す
ID3D12Fence* Fence::GetFence()
{
    return _fence.Get();
}

// フェンス値を返す
UINT Fence::GetFenceVal()
{
    return _fenceVal;
}
// フェンス値をインクリメントして返す
UINT Fence::GetIncrementFenceVal()
{
    _fenceVal++;
    return GetFenceVal();
}

Fence::Fence(){}
Fence::~Fence(){}