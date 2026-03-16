#include"VertBuff.h"
#include<cassert>

// 頂点バッファに書き込み
HRESULT VertBuff::WriteToVertBuff(ShogiObj* shogiObj)
{
    VertexStruct::Vertex* vertBuffMap;

    HRESULT result = _vertBuff->Map(
        0, nullptr, (void**)&vertBuffMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto vertices = shogiObj->GetVertices();
    std::copy(vertices.begin(), vertices.end(), vertBuffMap);

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