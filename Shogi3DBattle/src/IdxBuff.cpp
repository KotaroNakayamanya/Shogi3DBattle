#include"IdxBuff.h"
#include<memory>
#include<cassert>

// インデックスバッファに書き込み
HRESULT IdxBuff::WriteIdxBuff(std::vector<unsigned short> indexPtr)
{
    std::shared_ptr<unsigned short> idxMap;

    HRESULT result = _idxBuff->Map(
        0, nullptr, (void**)&idxMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto indices = indexPtr;
    
    std::copy(indices.begin(), indices.end(), idxMap.get());

    _idxBuff->Unmap(0, nullptr);
    
    return S_OK;
}

ID3D12Resource* IdxBuff::GetIdxBuff(){return _idxBuff.Get();} // インデックスバッファを返す

IdxBuff::IdxBuff(){}
IdxBuff::~IdxBuff(){}