#include"IdxBuff.h"

// インデックスに書き込み
HRESULT IdxBuff::WriteToIdxBuff(VertIndices* boardVertIndices, VertIndices* pieceVertIndices)
{
    USHORT* idxBuffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&idxBuffMap);
    if (FAILED(result)) return result;

    // インデックスをすべて繋げた配列を作成
    auto joinedIndices = boardVertIndices->GetVertIndices();
    auto tempIndices = pieceVertIndices->GetVertIndices();
    joinedIndices.insert(joinedIndices.end(), tempIndices.begin(), tempIndices.end());

    std::copy(joinedIndices.begin(), joinedIndices.end(), idxBuffMap);

    _buff->Unmap(0, nullptr);

    // バッファアドレスをそれぞれのオブジェクトに紐づける
    auto idxBuffAddress = _buff->GetGPUVirtualAddress();

    boardVertIndices->SetBuffAddress(idxBuffAddress);
    idxBuffAddress += boardVertIndices->GetVertIndicesByteSize();
    pieceVertIndices->SetBuffAddress(idxBuffAddress);
    
    return S_OK;
}

IdxBuff::IdxBuff(){}
IdxBuff::~IdxBuff(){}