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

// 頂点バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS VertBuff::GetAddress()
{
    return _vertBuff->GetGPUVirtualAddress();
}

// 頂点バッファを返す
ID3D12Resource* VertBuff::GetVertBuff(){return _vertBuff.Get();}

VertBuff::VertBuff(){}
VertBuff::~VertBuff(){}