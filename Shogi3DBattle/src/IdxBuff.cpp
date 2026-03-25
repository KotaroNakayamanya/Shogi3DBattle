#include"IdxBuff.h"


// インデックスに書き込み
HRESULT IdxBuff::WriteToIdxBuff(Board* board, std::vector<std::unique_ptr<Piece>>& pieces)
{
    USHORT* idxBuffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&idxBuffMap);
    if (FAILED(result)) return result;

    // インデックスをすべて繋げた配列を作成
    auto joinedIndices = board->GetIndices();
    for (auto& piece : pieces)
    {
        auto pieceIndices = piece->GetIndices();
        joinedIndices.insert(joinedIndices.end(), pieceIndices.begin(), pieceIndices.end());
    }

    std::copy(joinedIndices.begin(), joinedIndices.end(), idxBuffMap);

    _buff->Unmap(0, nullptr);

    // バッファアドレスをそれぞれのオブジェクトに紐づける
    auto idxAddress = _buff->GetGPUVirtualAddress();

    board->SetIdxAddress(idxAddress);
    idxAddress += board->GetIndicesByteSize();
    for (auto& piece : pieces)
    {
        piece->SetIdxAddress(idxAddress);
        idxAddress += piece->GetIndicesByteSize();
    }
    
    return S_OK;
}

IdxBuff::IdxBuff(){}
IdxBuff::~IdxBuff(){}