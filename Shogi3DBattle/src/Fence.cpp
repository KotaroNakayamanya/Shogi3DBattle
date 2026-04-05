#include"Fence.h"

void         Fence::SetFence(ComPtr<ID3D12Fence> fence){_fence = fence;}      // フェンスセット
ID3D12Fence* Fence::GetFence()                         {return _fence.Get();} // フェンスを返す

UINT64 Fence::GetFenceVal(){return _fence->GetCompletedValue();} // フェンス値を返す

// フェンス値をインクリメントして返す
unsigned int Fence::GetIncrementFenceVal()
{
    _fenceVal++;
    return GetFenceVal();
}