#include"VertBuff.h"

// 頂点バッファに書き込み
HRESULT VertBuff::WriteToVertBuff(Board* board, std::vector<std::unique_ptr<Piece>>& pieces)
{
    Vertices::Vert* vertBuffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&vertBuffMap);
    if (FAILED(result)) return result;

    // 頂点を全て繋げた配列を作成
    auto joinedVertices = board->GetVertices();
    for (auto& piece : pieces)
    {
        auto pieceVertices = piece->GetVertices();
        joinedVertices.insert(joinedVertices.end(), pieceVertices.begin(), pieceVertices.end());
    }

    std::copy(joinedVertices.begin(), joinedVertices.end(), vertBuffMap);

    _buff->Unmap(0, nullptr);


    // バッファアドレスをそれぞれのオブジェクトに紐づける
    auto vertAddress = _buff->GetGPUVirtualAddress();

    board->SetVertAddress(vertAddress);
    vertAddress += board->GetVerticesByteSize();
    for (auto& piece : pieces)
    {
        piece->SetVertAddress(vertAddress);
        vertAddress += piece->GetVerticesByteSize();
    }

    return S_OK;
}

VertBuff::VertBuff() {}
VertBuff::~VertBuff() {}