#include"VertBuff.h"
#include<cassert>

// 頂点バッファに書き込み
HRESULT VertBuff::WriteToVertBuff(Board* board, std::array<std::unique_ptr<Piece>, 40>& pieces)
{
    VertexStruct::Vertex* vertBuffMap;

    HRESULT result = _vertBuff->Map(0, nullptr, (void**)&vertBuffMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto boardVertices = board->GetVertices();

    auto joinedVertices = boardVertices;
    for (auto& piece : pieces)
    {
        auto pieceVertices = piece->GetVertices();
        joinedVertices.insert(joinedVertices.end(), pieceVertices.begin(), pieceVertices.end());
    }
    
    std::copy(joinedVertices.begin(), joinedVertices.end(), vertBuffMap);

    _vertBuff->Unmap(0, nullptr);

    return S_OK;
}

// 頂点バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS VertBuff::GetAddress()
{
    return _vertBuff->GetGPUVirtualAddress();
}

// 頂点バッファを返す
ID3D12Resource* VertBuff::GetVertBuff() { return _vertBuff.Get(); }

VertBuff::VertBuff() {}
VertBuff::~VertBuff() {}