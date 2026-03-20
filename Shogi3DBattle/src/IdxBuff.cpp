#include"IdxBuff.h"


// インデックスに書き込み
HRESULT IdxBuff::WriteToIdxBuff(Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces)
{
    unsigned short* idxBuffMap;

    HRESULT result = _idxBuff->Map(0, nullptr, (void**)&idxBuffMap);
    if (FAILED(result)) return result;

    // インデックスをすべて繋げた配列を作成
    auto joinedIndices = board->GetIndices();
    for (auto& piece : pieces)
    {
        auto pieceIndices = piece->GetIndices();
        joinedIndices.insert(joinedIndices.end(), pieceIndices.begin(), pieceIndices.end());
    }

    std::copy(joinedIndices.begin(), joinedIndices.end(), idxBuffMap);

    _idxBuff->Unmap(0, nullptr);

    // バッファアドレスをそれぞれのオブジェクトに紐づける
    auto idxAddress = _idxBuff->GetGPUVirtualAddress();

    board->SetIdxAddress(idxAddress);
    idxAddress += board->GetIndicesByteSize();
    for (auto& piece : pieces)
    {
        piece->SetIdxAddress(idxAddress);
        idxAddress += piece->GetIndicesByteSize();
    }
    
    return S_OK;
}

// 頂点バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS IdxBuff::GetAddress()
{
    return _idxBuff->GetGPUVirtualAddress();
}

IdxBuff::IdxBuff(){}
IdxBuff::~IdxBuff(){}