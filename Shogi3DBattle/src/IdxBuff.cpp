#include"IdxBuff.h"
#include<memory>
#include<cassert>

//// インデックスに書き込み
//HRESULT IdxBuff::WriteToIdxBuff(Board* board, Piece* piece)
//{
//    std::shared_ptr<unsigned short> idxBuffMap;
//
//    HRESULT result = _idxBuff->Map(0, nullptr, (void**)&idxBuffMap);
//    if (FAILED(result))
//    {
//        assert(false); return E_FAIL;
//    }
//
//    auto boardIndices = board->GetIndices();
//    auto pieceIndices = piece->GetIndices();
//
//    auto joinedIndices = boardIndices;
//    joinedIndices.insert(joinedIndices.end(), pieceIndices.begin(), pieceIndices.end());
//
//    std::copy(joinedIndices.begin(), joinedIndices.end(), idxBuffMap.get());
//
//    _idxBuff->Unmap(0, nullptr);
//    
//    return S_OK;
//}
// インデックスに書き込み
HRESULT IdxBuff::WriteToIdxBuff(Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces)
{
    std::shared_ptr<unsigned short> idxBuffMap;

    HRESULT result = _idxBuff->Map(0, nullptr, (void**)&idxBuffMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto boardIndices = board->GetIndices();
    auto joinedIndices = boardIndices;
    for (auto& piece : pieces)
    {
        auto pieceIndices = piece->GetIndices();
        joinedIndices.insert(joinedIndices.end(), pieceIndices.begin(), pieceIndices.end());
    }
    //auto pieceIndices = piece->GetIndices();

    //auto joinedIndices = boardIndices;
    //joinedIndices.insert(joinedIndices.end(), pieceIndices.begin(), pieceIndices.end());

    std::copy(joinedIndices.begin(), joinedIndices.end(), idxBuffMap.get());

    _idxBuff->Unmap(0, nullptr);
    
    return S_OK;
}

// 頂点バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS IdxBuff::GetAddress()
{
    return _idxBuff->GetGPUVirtualAddress();
}

IdxBuff::IdxBuff(){}
IdxBuff::~IdxBuff(){}