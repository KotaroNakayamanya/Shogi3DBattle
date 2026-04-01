#include"VertBuff.h"

//// 頂点バッファに書き込み
//HRESULT VertBuff::WriteToVertBuff(Board* board, std::vector<std::unique_ptr<Piece>>& pieces)
//{
//    Vertices::Vert* vertBuffMap;
//
//    HRESULT result = _buff->Map(0, nullptr, (void**)&vertBuffMap);
//    if (FAILED(result)) return result;
//
//    // 頂点を全て繋げた配列を作成
//    auto joinedVertices = board->GetVertices();
//    for (auto& piece : pieces)
//    {
//        auto pieceVertices = piece->GetVertices();
//        joinedVertices.insert(joinedVertices.end(), pieceVertices.begin(), pieceVertices.end());
//    }
//
//    //vertBuffMap += pieces[1]->GetVerticesByteSize();
//
//    //auto aaa = _buff->GetGPUVirtualAddress();
//    //vertBuffMap += 3;
//
//    //std::copy(joinedVertices.begin(), joinedVertices.end(), vertBuffMap);
//    for (auto& boardVert : board->GetVertices())
//    {
//        *vertBuffMap = boardVert;
//        vertBuffMap++;
//    }
//
//    for (auto& piece : pieces)
//    {
//        for (auto& pieceVert : piece->GetVertices())
//        {
//            *vertBuffMap = pieceVert;
//            vertBuffMap++;
//        }
//    }
//
//    //*vertBuffMap = joinedVertices[0];
//
//    //*vertBuffMap = joinedVertices[0];
//
//    _buff->Unmap(0, nullptr);
//
//
//    // バッファアドレスをそれぞれのオブジェクトに紐づける
//    auto vertAddress = _buff->GetGPUVirtualAddress();
//
//    board->SetBuffAddress(vertAddress);
//    vertAddress += board->GetVerticesByteSize();
//    for (auto& piece : pieces)
//    {
//        piece->SetBuffAddress(vertAddress);
//        vertAddress += piece->GetVerticesByteSize();
//    }
//
//    return S_OK;
//}

HRESULT VertBuff::WriteToBuff(Vertices* verticesObj, UINT idx)
{
    Vertices::Vert* vertBuffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&vertBuffMap);
    if (FAILED(result)) return result;

    vertBuffMap += idx;

    auto vertices = verticesObj->GetVertices();

    std::copy(vertices.begin(), vertices.end(), vertBuffMap);

    _buff->Unmap(0, nullptr);
}

VertBuff::VertBuff() {}
VertBuff::~VertBuff() {}