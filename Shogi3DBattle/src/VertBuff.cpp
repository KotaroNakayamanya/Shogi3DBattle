#include"VertBuff.h"
#include<cassert>

// 頂点バッファに書き込み
HRESULT VertBuff::WriteVertBuff(std::vector<VertexStruct::Vertex> vertexPtr)
{
    VertexStruct::Vertex* vertexMap;

    HRESULT result = _vertBuff->Map(
        0, nullptr, (void**)&vertexMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto vertices = vertexPtr;

    std::copy(vertices.begin(), vertices.end(), vertexMap);

    _vertBuff->Unmap(0, nullptr);

    return S_OK;
}

ID3D12Resource* VertBuff::GetVertBuff(){return _vertBuff.Get();} // 頂点バッファを返す

VertBuff::VertBuff(){}
VertBuff::~VertBuff(){}