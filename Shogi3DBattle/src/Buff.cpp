#include"Buff.h"

// バッファへ書き込み
template<typename T>
HRESULT Buff::WriteToBuff(std::vector<T> vec, unsigned int idx)
{
    T* buffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&buffMap);
    if (FAILED(result)) return result;

    buffMap += idx;

    std::copy(vec.begin(), vec.end(), buffMap);

    _buff->Unmap(0, nullptr);
}

D3D12_RESOURCE_DESC Buff::GetResourceDesc(){return _buff->GetDesc();} // リソースディスクリプタを返す



void            Buff::SetBuff(ComPtr<ID3D12Resource> buff){_buff = buff;}       // バッファセット
ID3D12Resource* Buff::GetBuff()                           {return _buff.Get();} // バックバッファを返す