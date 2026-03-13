#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

#include"VertexStruct.h"

class VertBuff
{
    friend class Device; // デバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _vertBuff; // 頂点バッファ

public:
    HRESULT WriteVertBuff(std::vector<VertexStruct::Vertex> vertexPtr); // 頂点バッファに書き込み
    ID3D12Resource* GetVertBuff(); // 頂点バッファを返す

    VertBuff();
    ~VertBuff();
};