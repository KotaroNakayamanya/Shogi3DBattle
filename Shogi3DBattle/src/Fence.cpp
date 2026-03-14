#include"Fence.h"

ID3D12Fence* Fence::GetFence(){return _fence.Get();} // フェンスを返す
UINT Fence::GetFenceVal(){return _fenceVal;} // フェンス値を返す

// フェンス値をインクリメントして返す
UINT Fence::GetIncrementFenceVal()
{
    _fenceVal++;
    return GetFenceVal();
}

Fence::Fence(){}
Fence::~Fence(){}